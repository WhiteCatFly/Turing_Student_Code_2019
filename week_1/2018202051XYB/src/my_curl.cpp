#include <string>
#include <iostream>
#include <fstream>

#include <curl/curl.h>
#include <curl/multi.h>

#include "my_curl.h"
#include "my_string.h"
#include "main.h"

size_t my_write(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string *str = dynamic_cast<std::string*>((std::string*)stream);
    if(size == 0 || ptr == NULL)
        return -1;
    char *p_data = (char*) ptr;
    str->append(p_data, nmemb * size);
    return nmemb * size;
}

// 单个链接设置
void easy_init(CURLM *cm, int x)
{
    CURL *eh = curl_easy_init();
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, my_write);
    curl_easy_setopt(eh, CURLOPT_WRITEDATA, (void*)results[x]);
    curl_easy_setopt(eh, CURLOPT_HEADER, 0L);
    curl_easy_setopt(eh, CURLOPT_URL, working[x].c_str());
    curl_easy_setopt(eh, CURLOPT_PRIVATE, working[x].c_str());
    curl_easy_setopt(eh, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(eh, CURLOPT_TIMEOUT_MS, MAX_EASY_TIME);

    curl_multi_add_handle(cm, eh);
}

// bfs 单次处理 waiting 队列内前 EASY_MAX 个 url
void multi(int &page_num)
{
    // multihandle 初始化
    CURLM *cm = NULL;
    CURL *eh = NULL;
    CURLMsg *msg = NULL;
    CURLcode return_code;
    int still_running = 0, msgs_left = 0;
    int http_status_code;
    const char *sz_url;
    page_num = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    cm = curl_multi_init();

    int index = 0;
    while(!waiting.empty() && index < EASY_MAX)
    {
        // 从 waiting 内取出 url 扔进 multihandle 的 working 队列
        std::string x = waiting.front();
        waiting.pop();
        working.push_back(x);
        std::string* page = new std::string();
        results.push_back(page);
        easy_init(cm, index);
        ++index;
    }

    // multi_perform()
    curl_multi_perform(cm, &still_running);
    do
    {
        curl_multi_perform(cm, &still_running);
    } while (still_running);
    
    // 读取单次 multihandle 结果
    while((msg = curl_multi_info_read(cm, &msgs_left))) 
    {
        if(msg->msg == CURLMSG_DONE)
        {
            eh = msg->easy_handle;
            return_code = msg->data.result;
            // error
            if(return_code != CURLE_OK)
            {
                // 28 网络问题链接失败 不记录 
                if(msg->data.result != 28)
                    ferr << "CURL error code: " << msg->data.result << std::endl;
                //continue;
            }

            // get http status code
            http_status_code = 0;
            sz_url = NULL;
            curl_easy_getinfo(eh, CURLINFO_RESPONSE_CODE, &http_status_code);
            curl_easy_getinfo(eh, CURLINFO_PRIVATE, &sz_url);

            if(http_status_code == 200)
            {
                // 单个网页爬取成功
                page_num++;
                fout << sz_url << std::endl;
            }
            else
            {
                // 单个网页爬取失败
                fail_time[sz_url]++;
                if(fail_time[sz_url] < MAX_FAIL_TIME)
                    waiting.push(sz_url);
                else
                    ferr << "GET of " << sz_url 
                        << " returned http status code "
                        << http_status_code << std::endl;
            }

            curl_multi_remove_handle(cm, eh);
            curl_easy_cleanup(eh);
        }
        else 
            ferr << "error: after curl_multi_info_read(), CURLMsg = "
                 << msg->msg << std::endl;
    }
    curl_multi_cleanup(cm);
}