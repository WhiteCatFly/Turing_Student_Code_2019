#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <curl/curl.h>
#include <curl/multi.h>

#include "my_res.h"
#include "my_fetcher.h"
#include "my_crawler.h"

extern my_crawler crawler;
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

void my_fetcher::init()
{
    curl_global_init(CURL_GLOBAL_ALL);
    cm = curl_multi_init();
    num = 0;
    still_running = 0;
    working.clear();
    for(auto r : results)
    {
        delete r;
    }
    results.clear();
}

std::vector<my_res> my_fetcher::fetch_batch(std::vector<std::string> batch)
{
    std::vector<my_res> ret;
    init();

    for(auto &u : batch)
        set_easy_handle(u);
                                               
    curl_multi_perform(cm, &still_running); // can be deleted?                                                                                                                                                                                                                                                                                                                                                                                                                                                                        )   
    do
    {
        curl_multi_perform(cm, &still_running);
    } while (still_running);
    

    CURLMsg *msg = NULL;
    int msgs_left = 0;

    while((msg = curl_multi_info_read(cm, &msgs_left)))
    {
        if(msg->msg == CURLMSG_DONE)
        {
            CURL *eh = msg->easy_handle;
            CURLcode return_code = msg->data.result;
            int http_status_code = 0;
            const char *sz_url = NULL;

            curl_easy_getinfo(eh, CURLINFO_RESPONSE_CODE, &http_status_code);
            curl_easy_getinfo(eh, CURLINFO_PRIVATE, &sz_url);

            // 处理不成功的
            if(return_code != CURLE_OK)
            {
                if(return_code != WEB_ERROR)
                    ferr << "CURL error code: " << msg->data.result << std::endl;
            }
            
            if(http_status_code == HTTP_TRANS)
            {
                ferr << "get http status code 301  : " << sz_url << std::endl;
            }

            if(http_status_code == HTTP_OK || http_status_code == HTTP_TRANS)
            {
                fout << sz_url << std::endl;
                crawler.set_success(std::string(sz_url));
            }
            else
            {
                int fail_time = crawler.query_fail_time(std::string(sz_url));
                ferr << "fail_time : " << fail_time
                     << "  GET of " << sz_url 
                     << " returned http status code "
                     << http_status_code << std::endl;
                

                if(fail_time < MAX_FAIL_TIME && http_status_code == HTTP_ERROR)
                {
                    crawler.add_url(std::string(sz_url));
                }
                if(http_status_code != HTTP_ERROR)
                {
                    crawler.set_fail(std::string(sz_url));
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
        if((*results[i]).empty() || crawler.query_fail(working[i])) 
            continue;
        my_res r;
        r.text = *results[i];
        r.url = working[i];
        ret.push_back(r);
    }
    return ret;
}

void my_fetcher::set_easy_handle(const std::string &url)
{
    CURL *eh = curl_easy_init();
    working.push_back(url);
    std::string *page = new std::string();
    results.push_back(page);
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, my_write);
    curl_easy_setopt(eh, CURLOPT_WRITEDATA, (void*)results[num]);
    curl_easy_setopt(eh, CURLOPT_HEADER, 0L);
    curl_easy_setopt(eh, CURLOPT_URL, working[num].c_str());
    curl_easy_setopt(eh, CURLOPT_PRIVATE, working[num].c_str());
    curl_easy_setopt(eh, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(eh, CURLOPT_TIMEOUT_MS, MAX_EASY_TIME);

    curl_multi_add_handle(cm, eh);
    ++num;
}
    