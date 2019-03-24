#include <curl/curl.h>

class CurlInit {
    CurlInit()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    ~CurlInit()
    {
        curl_global_cleanup();
    }
    static void _()
    {
        static CurlInit __curl_init;
    }
};
