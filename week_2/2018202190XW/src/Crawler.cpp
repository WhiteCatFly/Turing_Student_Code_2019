#include <set>
#include <queue>
#include <string>
#include <iostream>
#include <sys/time.h>

#include "Crawler.h"
#include "UrlParser.h"
#include "StringModify.h"

void make_dir(const std::string path) {
	std::string command = "mkdir " + path;
	int ret_value = system(command.c_str());
}

double get_time_used(const timeval &start_time) {
	timeval now_time;
	gettimeofday(&now_time, NULL);
	return now_time.tv_sec - start_time.tv_sec + (now_time.tv_usec - start_time.tv_usec) / 1000000.0;
}

int crawl(const std::string domain, const std::string root_url, const std::string save_file_folder, const timeval &start_time) {
	std::queue<std::string> waiting_url;
	std::set<std::string> visited_url;
	waiting_url.push(root_url);
	visited_url.insert(root_url);
	make_dir(save_file_folder);
	int page_num = 0;
	while (!waiting_url.empty()) {
		std::string current_url = waiting_url.front();
		waiting_url.pop();
		std::string savepath = current_url;
		modify_savepath(savepath);
		savepath = save_file_folder + savepath;
		const std::string command_prefix = "wget -t5 -T5 -o wget.log -O ";
		std::string current_command = command_prefix + escape_url(savepath) + " " + domain + escape_url(current_url);
		int ret_value = system(current_command.c_str());
		std::vector<std::string> new_urls;
		extract_url(domain, current_url, savepath, new_urls);
		for (auto new_url : new_urls) {
			if (!new_url.empty() && visited_url.find(new_url) == visited_url.end()) {
				visited_url.insert(new_url);
				waiting_url.push(new_url);
			}
		}
		page_num++;
		if (page_num % 10 == 0) {
			double time_used = get_time_used(start_time);
			std::cout << page_num << " pages downloaded  ----  " << time_used << "s used" << std::endl;
		}
	}
	return page_num;
}
