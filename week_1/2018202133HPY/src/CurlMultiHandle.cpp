#include "CurlMultiHandle.hpp"

int CurlMultiHandle::perform()
{
    int running;

    curl_multi_perform(multi_handle, &running);

    struct CURLMsg* m;

    for (auto it = easy_handles.begin(); it != easy_handles.end();) {
        if ((*it)->can_remove()) {
            curl_multi_remove_handle(multi_handle, **it);

            lookup.erase(**it);
            it = easy_handles.erase(it);
        } else {
            it++;
        }
    }

    if (std::unique_lock lock_this { lock_queue }; easy_handles.size() < max_num && wait_queue.size() > 0) {
        auto handle = wait_queue.front();

        handle->start();
        easy_handles.insert(handle);
        lookup[*handle] = handle;
        curl_multi_add_handle(multi_handle, *handle);

        wait_queue.pop_front();
        running = 1;
    }

    do {
        int msgq = 0;
        m = curl_multi_info_read(multi_handle, &msgq);
        if (m && (m->msg == CURLMSG_DONE)) {
            CURL* e = m->easy_handle;
            auto it = easy_handles.find(std::shared_ptr<SingleHandle>(lookup[e]));

            removeHandle(*it);
        }

    } while (m);

    return running;
}

int CurlMultiHandle::SingleHandle::curlProgressCallback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
    auto psingle = reinterpret_cast<SingleHandle*>(clientp);

    if (!psingle->header_received) {
        if (getNowTime() - psingle->start_time > (psingle->header_received ? 5 * timeout_ms : timeout_ms)) {
            psingle->TLE = true;
            return 1;
        }
    }

    return 0;
}
