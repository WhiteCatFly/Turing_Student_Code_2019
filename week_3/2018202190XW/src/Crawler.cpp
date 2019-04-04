#include <set>
#include <queue>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/time.h>

#include "Url.h"
#include "Crawler.h"
#include "StringModify.h"

void Crawler::set_start_time() {
	gettimeofday(&start_time, NULL);
}
double Crawler::get_time_used() const{
	timeval now_time;
	gettimeofday(&now_time, NULL);
	return now_time.tv_sec - start_time.tv_sec + (now_time.tv_usec - start_time.tv_usec) / 1000000.0;
}

int Crawler::crawl() {
	set_start_time();
	make_dir(save_file_folder);
	std::ofstream ostm("urls");

	std::queue<Url> waiting_url;
	std::set<Url> visited_url;
	waiting_url.push(root_url);
	visited_url.insert(root_url);

	int page_num = 0;
	while (!waiting_url.empty()) {
		Url current_url = waiting_url.front();
		waiting_url.pop();

		std::string savepath = current_url.get_savepath();
		savepath = save_file_folder + savepath;

		const std::string command_prefix = "wget -t5 -T5 -o wget.log -O ";
		std::string current_command = command_prefix + escape_url(savepath) + " " + domain + escape_url(current_url.str());
		int ret_value = system(current_command.c_str());

		std::vector<Url> new_urls;
		extract_url(current_url, savepath, new_urls);
		for (auto new_url : new_urls) {
			if (!new_url.empty() && visited_url.find(new_url) == visited_url.end()) {
				ostm << current_url.str() << " -> " << new_url.str() << std::endl;
				visited_url.insert(new_url);
				waiting_url.push(new_url);
			}
		}
		page_num++;
		if (page_num % 10 == 0) {
			double time_used = get_time_used();
			std::cout << page_num << " pages downloaded  ----  " << time_used << "s used" << std::endl;
		}
	}
	return page_num;
}

void Crawler::extract_url(const Url &current_url, const std::string savepath, std::vector<Url> &target) const{
	std::vector<Url> ret_value;
	std::string current_content;
	std::ifstream ifstrm(savepath);
	//const std::regex my_regex("<a[^<>]*?href=(\"([^@]*?)\"[^<>]*?>|\'([^@]*?)\'[^<>]*?>|([^@]*?)( [^<>]*?>|>))");
	const std::regex my_regex("href=(\"([^@]*?)\"|\'([^@]*?)\'|([^@]*?)( |>))");
	while (getline(ifstrm, current_content)) {
		std::smatch res;
		while (std::regex_search(current_content, res, my_regex)) {
			for (int i = 2; i <= 4; i++) if (res[i].str().size() != 0) {
				std::string extract_value = res[i].str();
				extract_value = replace_sub_string(extract_value, "&amp;", "&");
				Url new_url(extract_value);
				new_url.normalize(domain, current_url);
				target.push_back(new_url);
			}
			current_content = res.suffix();
		}
	}
}