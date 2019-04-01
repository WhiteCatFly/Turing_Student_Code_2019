#ifndef _COWR_EVENTLOOP_EVENTLOOP

#define _COWR_EVENTLOOP_EVENTLOOP

#include <thread>
#include <vector>

#include <sys/signalfd.h>

#include "Event.hpp"
#include "Worker.hpp"

#include "../Utils/Config.hpp"
#include "../Utils/Logger.hpp"

namespace cowr {

class EventLoop {
private:
    const static inline int worker_num = 8;

    int now = 0;
    std::vector<Worker> workers;
    std::set<std::shared_ptr<Event>, Event::cmp_shared_ptr> events;

    std::recursive_mutex lock_que;

    int sigfd;

    Worker& getNextWorker()
    {
        Worker& ret = workers[now];
        now++;
        if (now == workers.size())
            now = 0;

        return ret;
    }

    EventLoop()
    {
        workers = std::vector<Worker>(std::stoi(Config::getInstance()["EventLoop"]["workers"]));

        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGALRM);
        sigfd = signalfd(-1, &sigset, 0);

        sigprocmask(SIG_BLOCK, &sigset, NULL);
        signal(SIGALRM, SIG_IGN);

        for (auto& worker : workers) {
            worker.startLoop();
        }

        Logger::getInstance().info("EventLoop initialized");
    }

    void wait(int fd, millisecond_t timeout_ms);

public:
    static EventLoop& getInstance();

    void addCurlHandle(std::shared_ptr<CurlMultiHandle::SingleHandle> easy_handle)
    {
        auto& worker = getNextWorker();
        worker.addCurlHandle(easy_handle);
    }

    std::shared_ptr<Event> callLater(millisecond_t delay, std::function<void()> callback)
    {
        std::unique_lock _(lock_que);
        auto&& it = *(events.insert(std::make_shared<Event>(getNowTime() + delay, callback)).first);

        kill(getpid(), SIGALRM);

        return it;
    }

    void loop(millisecond_t delay);

    void loop_until_done();
};
}
#endif
