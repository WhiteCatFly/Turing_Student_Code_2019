#include <set>
#include <queue>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/time.h>

#include "Url.h"
#include "TagNode.h"
#include "Html.h"
#include "Crawler.h"
#include "StringModify.h"

const std::string Crawler::black_list[] = {
	"@",
	"script",
	"css",
	"js",
	"pdf",
	"xlsx",
	"xls",
	"doc",
	"docx"
};

void Crawler::set_start_time() {
	gettimeofday(&start_time, NULL);
}
double Crawler::get_time_used() const{
	timeval now_time;
	gettimeofday(&now_time, NULL);
	return now_time.tv_sec - start_time.tv_sec + (now_time.tv_usec - start_time.tv_usec) / 1000000.0;
}

Html Crawler::get_url(Url url, std::ofstream &log_strm) const{
	std::string path = download_path + url.get_savepath();

	const std::string command_prefix = "wget -t3 -T3 -o wget.log -O ";
	std::string current_command = command_prefix + escape_url(path) + " " + escape_url(url.get_path());
	int ret_value = system(current_command.c_str());
	if (check_file_size(path) == 0) log_strm << "download failed: " << url.get_path() << std::endl;
	Html ret_html(path);
	return ret_html;
}

int Crawler::crawl() {
	std::ofstream log_strm("crawl.log");

	set_start_time();
	make_dir(download_path);

	int num_of_loaded_pages = 0;
	int num_of_lost_pages = 0;

	if (visited_urls.size()) {
		std::cout << "loading..." << std::endl;
		for (auto visited_url : visited_urls) {
			int size = check_file_size(download_path + visited_url.get_savepath());
			if (size != -1) num_of_loaded_pages++;
			if (size == 0) {
				num_of_lost_pages++;
				get_url(visited_url, log_strm);
			}
		}
		std::cout << "finished loading." << std::endl;
		std::cout << num_of_loaded_pages << " pages had been loaded" << std::endl;
		std::cout << num_of_lost_pages << " pages was lost and download again" << std::endl;
	}

	int num_of_new_pages = 0;
	while (!waiting_urls.empty()) {
		Url current_url = waiting_urls.front();
		waiting_urls.pop();

		Html now_page = get_url(current_url, log_strm);

		std::vector<Url> new_urls;
		extract_url(current_url, download_path + current_url.get_savepath(), new_urls);
		
		for (auto new_url : new_urls) {
			if (!new_url.empty() && visited_urls.find(new_url) == visited_urls.end()) {
				visited_urls.insert(new_url);
				waiting_urls.push(new_url);
			}
		}
		num_of_new_pages++;
		if (num_of_new_pages % 100 == 0) save_load(log_strm);
		if (num_of_new_pages % 10 == 0) {
			double time_used = get_time_used();
			std::cout << num_of_new_pages << " new pages downloaded  ----  " << (int)time_used << "s used  ----  " <<
				num_of_loaded_pages + num_of_new_pages << " pages in total" << std::endl;
		}
	}
	return num_of_new_pages;
}

void Crawler::extract_url(const Html &my_html, const Url &referer, std::vector<Url> &target) const{
	std::vector<std::string> urls = my_html.parse_href();
	for (auto url : urls) {
		bool banned = false;
		for (auto s : black_list) {
			if (url.find(s) != std::string::npos) {
				banned = true;
				break;
			}
		}
		if (banned) continue;
			url = replace_sub_string(url, "&amp;", "&");
			target.push_back(Url(url));
	}
}

void Crawler::save_load(std::ofstream &log_strm) {
	std::queue<Url> tmp;
	std::ofstream ostrm(save_file_path);
	while (!waiting_urls.empty()) {
		Url h = waiting_urls.front();
		waiting_urls.pop();
		tmp.push(h);
		ostrm << "w " << h.get_path() << std::endl;
	}
	waiting_urls = tmp;
	for (auto url : visited_urls) {
		ostrm << "v " << url.get_path() << std::endl;
	}
	log_strm << "saveloaded! " << waiting_urls.size() << " pages in queue " <<
		visited_urls.size() << " pages in set" << std::endl;
}

void Crawler::extract_url(const Url &referer, const std::string savepath, std::vector<Url> &target) const{
	std::vector<Url> ret_value;
	std::string current_content;
	std::ifstream ifstrm(savepath);
	const std::regex my_regex("href=(\"([^@]*?)\"|\'([^@]*?)\'|([^@]*?)( |>))");
	while (getline(ifstrm, current_content)) {
		std::smatch res;
		while (std::regex_search(current_content, res, my_regex)) {
			for (int i = 2; i <= 4; i++) if (res[i].str().size() != 0) {
				std::string extract_value = res[i].str();
				extract_value = replace_sub_string(extract_value, "&amp;", "&");
				bool banned = false;
				for (auto s : black_list) {
					if (extract_value.find(s) != std::string::npos) {
						banned = true;
						break;
					}
				}
				if (banned) break;
				Url new_url(extract_value);
				new_url.normalize(referer.get_path());
				if (new_url.get_path().size()) target.push_back(new_url);
			}
			current_content = res.suffix();
		}
	}
}