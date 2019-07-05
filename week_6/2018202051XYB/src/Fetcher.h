#ifndef _FETCHER_H
#define _FETCHER_H

#include <vector>
#include <string>

#include <curl/curl.h>
#include <curl/multi.h>

#include "res.h"

#define HTTP_OK 200
#define HTTP_ERROR 0
#define HTTP_TRANS 301
#define WEB_ERROR 28

class Fetcher
{
private:
    int num;
    CURLM *cm;
    int stillRunning;
    std::vector<std::string> working;
    std::vector<std::string*> results;
public:
    void init();
    void setEasyHandle(const std::string &url);
    std::vector<res> fetchBatch(std::vector<std::string> batch);
};

size_t my_write(void *ptr, size_t size, size_t nmemb, void *stream);


#endif