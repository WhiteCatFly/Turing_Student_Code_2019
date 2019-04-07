#include "web_crawler.h"
#include <cstdio>
#include <string>
#include <set>
#include <queue>

void bfs(){
	std::queue<std::string> url_queue;
	while (!url_queue.empty())
		url_queue.pop();
	std::set<std::string> url_set;
	url_set.clear();
	
	int total = 0;
	std::string origin = "info.ruc.edu.cn/";
	url_queue.push(origin);
	url_set.insert(origin);
	while (!url_queue.empty()){
		std::string present_url = url_queue.front();
		std::string present_html = "";
		url_queue.pop();
		get_html(present_url, present_html, ++total);
		find_next_url(present_url, present_html, url_queue, url_set);
	}
	printf("There are %d websites in http://info.ruc.edu.cn.\n", total);	
}