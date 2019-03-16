#ifndef _COWR_CURLMULTIHANDLE

#define _COWR_CURLMULTIHANDLE

#include <curl/curl.h>

#include <list>
#include <memory>
#include <set>

#include "CurlEasyHandle.hpp"
#include "timeutil.hpp"

class CurlMultiHandle {
public:
    class SingleHandle : public CurlEasyHandle {
    protected:
        bool to_remove;
        bool header_received;
        bool TLE;
        millisecond_t start_time;
        std::function<void(CurlEasyHandle&)> on_request_done = curlDefaultRequestDoneHandler;

    public:
        constexpr inline static int timeout_ms = 1000;

        SingleHandle()
            : CurlEasyHandle()
            , to_remove(false)
            , header_received(false)
            , TLE(false)
        {
            // curl_easy_setopt(*this, CURLOPT_TIMEOUT_MS, (long)timeout_ms);
            curl_easy_setopt(*this, CURLOPT_XFERINFOFUNCTION, curlProgressCallback);
            curl_easy_setopt(*this, CURLOPT_XFERINFODATA, this);
        }

        SingleHandle(const SingleHandle&) = delete;
        SingleHandle(SingleHandle&& r)
            : CurlEasyHandle(std::move(r))
        {
            std::unique_lock lock_r { r.lock };
            to_remove = r.to_remove;
            on_request_done = std::move(r.on_request_done);
        }

        void start()
        {
            std::unique_lock lock_this { lock };
            start_time = getNowTime();
        }

        millisecond_t getStartTime()
        {
            std::unique_lock lock_this { lock };
            return start_time;
        }

        void remove(bool doRequestDone = true)
        {
            std::unique_lock lock_this { lock };

            to_remove = true;

            if (doRequestDone)
                onRequestDone();
        }

        bool can_remove() const
        {
            return to_remove;
        }

        void onRequestDone()
        {
            std::unique_lock lock_this { lock };

            on_request_done(*this);
        }

        CURLcode setRequestDoneHandler(std::function<void(CurlEasyHandle&)> handler)
        {
            std::unique_lock lock_this { lock };

            on_request_done = handler;
            return CURLE_OK;
        }

        bool isTLE()
        {
            return TLE;
        }

        void setHeaderDone()
        {
            header_received = true;
        }

        auto getRequestDoneHandler()
        {
            std::unique_lock lock_this { lock };
            return on_request_done;
        }

        static void curlDefaultRequestDoneHandler(CurlEasyHandle& easy_handle)
        {
        }

        static int curlProgressCallback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
    };

protected:
    std::recursive_mutex lock_queue;

    CURLM* multi_handle;

    int max_num = 32;

    std::list<std::shared_ptr<SingleHandle>> wait_queue;
    std::set<std::shared_ptr<SingleHandle>> easy_handles;
    std::map<CURL*, std::weak_ptr<SingleHandle>> lookup;

public:
    CurlMultiHandle()
        : multi_handle(curl_multi_init())
    {
    }

    CurlMultiHandle(const CurlMultiHandle&) = delete;
    CurlMultiHandle(CurlMultiHandle&& r)
    {
        std::unique_lock lock_r { r.lock_queue };

        multi_handle = r.multi_handle;
        r.multi_handle = nullptr;

        max_num = r.max_num;

        wait_queue = std::move(r.wait_queue);
        easy_handles = std::move(r.easy_handles);
        lookup = std::move(r.lookup);
    }

    ~CurlMultiHandle()
    {
        for (auto easy_handle : easy_handles)
            curl_multi_remove_handle(multi_handle, *easy_handle);
        if (multi_handle)
            curl_multi_cleanup(multi_handle);
    }

    CURLMcode addHandle(std::shared_ptr<SingleHandle> easy_handle)
    {
        std::unique_lock lock_this { lock_queue };

        wait_queue.push_back(easy_handle);
        return CURLM_OK;
    }

    void removeHandle(std::shared_ptr<SingleHandle> easy_handle)
    {
        easy_handle->remove();
    }

    int perform();

    size_t size()
    {
        std::unique_lock lock_this { lock_queue };
        return lookup.size() + wait_queue.size();
    }

    operator CURLM*()
    {
        return multi_handle;
    }
};

#endif
