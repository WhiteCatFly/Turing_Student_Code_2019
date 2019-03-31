#ifndef _MY_CURL_H
#define _MY_CURL_H

#include <curl/curl.h>
#include <curl/multi.h>

// MAC_FAIL_TIME : 失败重连次数上限
#define MAX_FAIL_TIME 5
// MAC_EASY_TIME : 单次链接时间上限（ms）
#define MAX_EASY_TIME 1500L
// EASY_MAX : 单次 multihandle 处理上限
#define EASY_MAX 64

size_t my_write(void *ptr, size_t size, size_t nmemb, void *stream);

// 单个链接设置
void easy_init(CURLM *cm, int x);

// bfs 单次处理 waiting 队列内前 EASY_MAX 个 url
void multi(int &page_num);


#endif