#ifndef _COWR_EVENTLOOP

#define _COWR_EVENTLOOP

#include <thread>
#include <vector>

#include <sys/signalfd.h>

#include "Event.hpp"
#include "Worker.hpp"

class EventLoop {
private:
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
        : workers(8)
    {

        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGALRM);
        sigfd = signalfd(-1, &sigset, 0);

        sigprocmask(SIG_BLOCK, &sigset, NULL);
        signal(SIGALRM, SIG_IGN);

        for (auto& worker : workers) {
            worker.startLoop();
        }
    }

    void wait(int fd, millisecond_t timeout_ms);

public:
    static EventLoop& getEventLoop();

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

extern EventLoop& global_loop;

#endif
