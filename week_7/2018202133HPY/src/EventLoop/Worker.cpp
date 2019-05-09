#include "Worker.hpp"

#include <algorithm>

namespace cowr {

thread_local Worker* Worker::worker_this_thread;

void Worker::loop(millisecond_t delay)
{
    worker_this_thread = this;
    worker_thread_id = pthread_self();

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, NULL);

    millisecond_t end_time = getNowTime() + delay;

    while (delay < 0 || (getNowTime() < end_time)) {

        int running = 0;

        {
            running = curl_multi_handle.perform();
        }

        {
            std::unique_lock _(lock_que);
            while (events.size() > 0 && (*events.begin())->time < getNowTime()) {
                auto it = events.begin();
                _.unlock();

                (*it)->callback();

                _.lock();
                events.erase(it);

                running = 1;
            }
        }

        {
            fd_set read_set, write_set, exc_set;
            int max_fd;

            curl_multi_fdset(curl_multi_handle, &read_set, &write_set, &exc_set, &max_fd);

            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 10000;

            select(max_fd, &read_set, &write_set, &exc_set, &timeout);
        }

        // if (!running)
        //     usleep(5000);
    }
}
}
