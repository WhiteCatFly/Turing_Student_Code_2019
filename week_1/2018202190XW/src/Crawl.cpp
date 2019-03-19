#include <set>
#include <queue>
#include <string>
#include <iostream>
#include <sys/time.h>

#include "Crawl.h"
#include "UrlParser.h"
#include "StringModify.h"

const std::string command_prefix = "wget -t5 -T5 -o wget.log -O ";
extern const std::string domain = "http://info.ruc.edu.cn/";
const std::string root_url = "index.php";

timeval start_time, end_time, now_time;

int crawl(std::string root_url) {
	std::queue<std::string> waiting_url;
	std::set<std::string> visited_url;
	waiting_url.push(root_url);
	visited_url.insert(root_url);
	int ret_value = system("mkdir page/");
	int page_num = 0;
	while (!waiting_url.empty()) {
		std::string current_url = waiting_url.front();
		waiting_url.pop();
		std::string savepath = current_url;
		modify_savepath(savepath);
		savepath = "page/" + savepath;
		std::string current_command = command_prefix + escape_url(savepath) + " " + domain + escape_url(current_url);
		int ret_value = system(current_command.c_str());
		std::vector<std::string> new_urls;
		extract_url(current_url, savepath, new_urls);
		for (auto new_url : new_urls) {
			if (!new_url.empty() && visited_url.find(new_url) == visited_url.end()) {
				visited_url.insert(new_url);
				waiting_url.push(new_url);
			}
		}
		page_num++;
		if (page_num % 10 == 0) {
			gettimeofday(&now_time, NULL);
			double time_use = now_time.tv_sec - start_time.tv_sec + (now_time.tv_usec - start_time.tv_usec) / 1000000.0;
			std::cout << page_num << " pages downloaded  ----  " << time_use << "s used" << std::endl;
		}
	}
	return page_num;
}

int main() {
	gettimeofday(&start_time, NULL);
	int total_num = crawl(root_url);
	std::cout << "finished!  total: " << total_num << " pages" << std::endl;
	return 0;
}