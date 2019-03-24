#include "EventLoop.hpp"

#include <sys/signalfd.h>

#include <algorithm>

EventLoop& global_loop = EventLoop::getEventLoop();

EventLoop& EventLoop::getEventLoop()
{
    static EventLoop global_event_loop;
    return global_event_loop;
}

void EventLoop::wait(int fd, millisecond_t timeout_ms)
{
    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);
    timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = timeout_ms % 1000 * 1000;
    select(fd + 1, &fdset, NULL, NULL, &timeout);

    if (FD_ISSET(fd, &fdset)) {
        struct signalfd_siginfo info;
        read(fd, &info, sizeof info);
    }

    {
        std::unique_lock _ { lock_que };
        while (events.size()) {
            auto it = events.begin();
            if ((*it)->time <= getNowTime()) {
                getNextWorker().callAt((*it)->time, (*it)->callback);
                events.erase(it);
            } else {
                struct itimerval next_timeout;
                millisecond_t timeout = (*it)->time - getNowTime();
                next_timeout.it_interval.tv_sec = 0;
                next_timeout.it_interval.tv_usec = 0;
                next_timeout.it_value.tv_sec = std::max(timeout / 1000, 0LL);
                next_timeout.it_value.tv_usec = std::max(timeout % 1000 * 1000, 10000LL);
                setitimer(ITIMER_REAL, &next_timeout, NULL);
                break;
            }
        }
    }
}

void EventLoop::loop(millisecond_t delay)
{
    //TODO
    if (delay < 0)
        while (true)
            wait(sigfd, 1000);
    else {
        millisecond_t end = getNowTime() + delay;
        while (getNowTime() < end)
            wait(sigfd, 10);
    }
}

void EventLoop::loop_until_done()
{
    bool running = true;

    while (running) {
        if (std::unique_lock _ { lock_que }; events.size())
            goto next;
        for (auto& worker : workers) {
            if (worker.size())
                goto next;
        }
        break;
    next:
        wait(sigfd, 1000);
    }
}
