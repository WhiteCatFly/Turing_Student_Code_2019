#ifndef _COWR_EVENTLOOP_WORKER

#define _COWR_EVENTLOOP_WORKER

#include <signal.h>

#include <memory>
#include <random>
#include <set>
#include <thread>

#include "../Curl/CurlMultiHandle.hpp"
#include "Event.hpp"

namespace cowr {

class Worker {
protected:
    std::set<std::shared_ptr<Event>, Event::cmp_shared_ptr> events;
    CurlMultiHandle curl_multi_handle;

    std::unique_ptr<std::thread> worker_thread;
    pthread_t worker_thread_id;

    std::recursive_mutex lock_que;
    static thread_local Worker* worker_this_thread;

    void loop(millisecond_t delay);

public:
    Worker() {}

    Worker(const Worker&) = delete;
    Worker(Worker&& r) = delete;

    Worker& operator=(const Worker&) = delete;
    Worker& operator=(Worker&&) = delete;

    void startLoop()
    {

        worker_thread = std::unique_ptr<std::thread> {
            new std::thread {
                [this]() -> void {
                    loop(-1);
                } }
        };
        worker_thread->detach();
    }

    void addCurlHandle(std::shared_ptr<CurlMultiHandle::SingleHandle> easy_handle)
    {
        curl_multi_handle.addHandle(easy_handle);
    }

    void removeCurlHandle(std::shared_ptr<CurlMultiHandle::SingleHandle> easy_handle)
    {
        curl_multi_handle.removeHandle(easy_handle);
    }

    std::shared_ptr<Event> callLater(millisecond_t delay, std::function<void()> callback)
    {
        std::unique_lock _(lock_que);
        return *(events.insert(std::make_shared<Event>(getNowTime() + delay, callback)).first);
    }

    std::shared_ptr<Event> callAt(millisecond_t time, std::function<void()> callback)
    {
        std::unique_lock _(lock_que);
        return *(events.insert(std::make_shared<Event>(time, callback)).first);
    }

    std::shared_ptr<Event> callAt(std::shared_ptr<Event>& pevent)
    {
        std::unique_lock _(lock_que);
        return *(events.insert(pevent).first);
    }

    size_t size()
    {
        std::unique_lock _ { lock_que };
        return events.size() + curl_multi_handle.size();
    }
};
}

#endif
