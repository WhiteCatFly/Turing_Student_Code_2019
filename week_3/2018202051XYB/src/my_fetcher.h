#ifndef _MY_FETCHER_H
#define _MY_FETCHER_H

#include <vector>
#include <string>

#include <curl/curl.h>
#include <curl/multi.h>

#include "my_res.h"

#define HTTP_OK 200
#define HTTP_ERROR 0
#define HTTP_TRANS 301
#define WEB_ERROR 28

class my_fetcher
{
private:
    int num;
    CURLM *cm;
    int still_running;
    std::vector<std::string> working;
    std::vector<std::string*> results;
public:
    
    void init();
    void set_easy_handle(const std::string &url);
    std::vector<my_res> fetch_batch(std::vector<std::string> batch);
};

size_t my_write(void *ptr, size_t size, size_t nmemb, void *stream);


#endif