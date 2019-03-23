#include "web_crawler.h"
#include <string>
#include <set>
#include <queue>

void find_next_url(const std::string &present_url, const std::string &present_html, std::queue<std::string> &url_queue, std::set<std::string> &url_set){
	int url_begin = present_html.find("href=");
	while (url_begin != -1){
		int url_end = present_html.find(present_html[url_begin + 5] == '\"' ? '\"' : '\'', url_begin + 6);
		std::string new_url = present_html.substr(url_begin + 6, url_end - url_begin - 6);
		url_begin = present_html.find("href=", url_end);
		if (new_url.find("info.ruc") != new_url.npos){
			if (new_url.find("http:") != new_url.npos)
				new_url.erase(0,7);
		}
		else if (new_url.find("http") == new_url.npos){
				new_url = present_url.substr(0, present_url.find_last_of('/') + 1) + new_url;
			}
		if (new_url.find("info.ruc") != new_url.npos){
			int flag = 0;
			for (int i = 0; forbidden_words[i] != "end"; ++i){
				if (new_url.find(forbidden_words[i]) != new_url.npos){
					flag = 1;
					break;
				}
			}
			if (flag)
				continue;
			if (!url_set.count(new_url)){
				url_set.insert(new_url);
				url_queue.push(new_url);
			}
		}
	}
}