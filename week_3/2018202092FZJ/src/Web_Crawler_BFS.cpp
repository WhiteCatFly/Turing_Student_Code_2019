#include "Web_Crawler.h"
#include <set>
#include <string>
#include <queue>
#include <cstdio>

void Web_Crawler::Web_Crawler_BFS(const char* crawled_web){
	origin = crawled_web;
	url_queue.push(origin);
	url_set.insert(origin);
	while (!url_queue.empty()){
		current_url = url_queue.front();
		url_queue.pop();
		++total_website;
		get_html();
		find_next_url();
	}
	printf("There are %d websites in %s, which includes %d websites downloaded successfully and %d websites downloaded unsuccessfully.\n", total_website, crawled_web, successful_website, failed_website);
}
