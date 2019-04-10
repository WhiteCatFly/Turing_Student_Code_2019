#ifndef _COWR_CURL_CURLEASYHANDLE

#define _COWR_CURL_CURLEASYHANDLE

#include <curl/curl.h>

#include <functional>
#include <iostream>
#include <map>
#include <mutex>

namespace cowr {

class CurlEasyHandle {
protected:
    std::recursive_mutex lock;
    CURL* handle;

    std::map<std::string, std::string> env;

    std::function<void(void*, size_t, size_t, CurlEasyHandle&)> on_data_receive = curlDefaultDataReceiveHandler;
    std::function<void(CurlEasyHandle&)> on_header_receive = curlDefaultHeaderReceiveHandler;

public:
    CurlEasyHandle()
    {
        handle = curl_easy_init();

        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, curlDataHandleFunc);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, curlHeaderHandleFunc);
        curl_easy_setopt(handle, CURLOPT_HEADERDATA, this);
        curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36");

        setCanRedirect(true);
    }

    ~CurlEasyHandle()
    {
        if (handle)
            curl_easy_cleanup(handle);
    }

    CurlEasyHandle(const CurlEasyHandle&) = delete;

    CurlEasyHandle(CurlEasyHandle&& r)
    {
        std::lock_guard lock_r { r.lock };
        env = std::move(r.env);
        on_data_receive = std::move(r.on_data_receive);
        on_header_receive = std::move(r.on_header_receive);
        handle = r.handle;
        r.handle = nullptr;
    }

    template <typename T>
    CURLcode setOption(CURLoption option, T args)
    {
        std::lock_guard lock_this { lock };
        return curl_easy_setopt(handle, option, args);
    }

    CURLcode setURL(std::string URI)
    {
        std::lock_guard lock_this { lock };
        return curl_easy_setopt(handle, CURLOPT_URL, URI.c_str());
    }

    CURLcode setDataReceiveHandler(std::function<void(void*, size_t, size_t, CurlEasyHandle&)> handler)
    {
        std::lock_guard lock_this { lock };
        on_data_receive = handler;
        return CURLE_OK;
    }

    CURLcode setHeaderReceiveHandler(std::function<void(CurlEasyHandle&)> handler)
    {
        std::lock_guard lock_this { lock };
        on_header_receive = handler;
        return CURLE_OK;
    }

    CURLcode setCanRedirect(bool redirect)
    {
        std::lock_guard lock_this { lock };
        return curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, long(redirect));
    }

    std::string getURL()
    {
        std::lock_guard lock_this { lock };
        char* url = NULL;
        curl_easy_getinfo(handle, CURLINFO_EFFECTIVE_URL, &url);
        return url;
    }

    virtual CURLcode perform()
    {
        std::lock_guard lock_this { lock };
        return curl_easy_perform(handle);
    }

    operator CURL*()
    {
        return handle;
    }

    auto getenv() const
    {
        std::lock_guard lock_this { const_cast<std::recursive_mutex&>(lock) };
        return env;
    }

    static size_t curlDefaultDataReceiveHandler(void* buffer, size_t size, size_t nmemb, CurlEasyHandle& easy_handle)
    {
        std::cout.write((const char*)buffer, nmemb);
        std::cout.flush();
        return nmemb;
    }

    static void curlDefaultHeaderReceiveHandler(CurlEasyHandle& easy_handle)
    {
    }

    static size_t curlDataHandleFunc(void* buffer, size_t size, size_t nmemb, void* userp)
    {
        ((CurlEasyHandle*)userp)->on_data_receive(buffer, size, nmemb, *(CurlEasyHandle*)userp);
        return nmemb;
    }

    static size_t curlHeaderHandleFunc(void* buffer, size_t size, size_t nmemb, void* userp);
};
}

#endif
