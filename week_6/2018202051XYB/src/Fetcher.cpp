#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <curl/curl.h>
#include <curl/multi.h>

#include "res.h"
#include "Fetcher.h"
#include "Crawler.h"

extern Crawler crawler;
extern std::ofstream ferr, fout;
extern int MAX_FAIL_TIME, 
           MAX_EASY_TIME;


size_t my_write(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string *str = dynamic_cast<std::string*>((std::string*)stream);
    if(size == 0 || ptr == NULL)
        return -1;
    char *p_data = (char*) ptr;
    str->append(p_data, nmemb * size);
    return nmemb * size;
}

void Fetcher::init()
{
    curl_global_init(CURL_GLOBAL_ALL);
    cm = curl_multi_init();
    num = 0;
    stillRunning = 0;
    working.clear();
    for(auto r : results)
    {
        delete r;
    }
    results.clear();
}

std::vector<res> Fetcher::fetchBatch(std::vector<std::string> batch)
{
    std::vector<res> ret;
    init();

    for(auto &u : batch)
        setEasyHandle(u);
                                               
    curl_multi_perform(cm, &stillRunning); // can be deleted?                                                                                                                                                                                                                                                                                                                                                                                                                                                                        )   
    do
    {
        curl_multi_perform(cm, &stillRunning);
    } while (stillRunning);

    CURLMsg *msg = NULL;
    int msgsLeft = 0;

    while((msg = curl_multi_info_read(cm, &msgsLeft)))
    {
        if(msg->msg == CURLMSG_DONE)
        {
            CURL *eh = msg->easy_handle;
            CURLcode returnCode = msg->data.result;
            int httpStatusCode = 0;
            const char *tmpUrl = NULL;

            curl_easy_getinfo(eh, CURLINFO_RESPONSE_CODE, &httpStatusCode);
            curl_easy_getinfo(eh, CURLINFO_EFFECTIVE_URL, &tmpUrl);            

            // 处理不成功的
            if(returnCode != CURLE_OK)
            {
                if(returnCode != WEB_ERROR)
                    ferr << "CURL error code: " << msg->data.result << std::endl;
            }
            
            if(httpStatusCode == HTTP_TRANS)
            {
                ferr << "get http status code 301  : " << tmpUrl << std::endl;
            }

            if(httpStatusCode == HTTP_OK || httpStatusCode == HTTP_TRANS)
            {
                fout << tmpUrl << std::endl;
                crawler.setSuccess(std::string(tmpUrl));
            }
            else
            {
                int fail_time = crawler.queryFailTime(std::string(tmpUrl));
                ferr << "fail_time : " << fail_time
                     << "  GET of " << tmpUrl 
                     << " returned http status code "
                     << httpStatusCode << std::endl;
                

                if(fail_time < MAX_FAIL_TIME && httpStatusCode == HTTP_ERROR)
                {
                    crawler.addUrl(std::string(tmpUrl));
                }
                if(httpStatusCode != HTTP_ERROR)
                {
                    crawler.setFail(std::string(tmpUrl));
                }
            }
        }
        else
        {
            ferr << "error: after curl_multi_info_read(), CURLMsg = "
                 << msg->msg << std::endl;
        }
    }
    curl_multi_cleanup(cm);

    for(int i = 0; i < num; i++)
    {
        if((*results[i]).empty() || crawler.queryFail(working[i])) 
            continue;
        res r;
        r.text = *results[i];
        r.url = working[i];
        ret.push_back(r);
    }
    return ret;
}

void Fetcher::setEasyHandle(const std::string &url)
{
    CURL *eh = curl_easy_init();
    working.push_back(url);
    std::string *page = new std::string();
    results.push_back(page);
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, my_write);
    curl_easy_setopt(eh, CURLOPT_WRITEDATA, (void*)results[num]);
    curl_easy_setopt(eh, CURLOPT_HEADER, 0L);
    curl_easy_setopt(eh, CURLOPT_URL, working.back().c_str());
    curl_easy_setopt(eh, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(eh, CURLOPT_TIMEOUT_MS, MAX_EASY_TIME);

    curl_multi_add_handle(cm, eh);
    ++num;
}