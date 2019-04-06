#include <string>
#include <iostream>
#include <sys/time.h>

#include "Crawler.h"

const std::string default_domain = "http://info.ruc.edu.cn/";
const std::string default_root_url = "index.php";
const std::string default_save_file_folder = "page/";

int main() {
	timeval start_time;
	std::string domain, root_url, save_file_folder;
	std::cout << "Input domain: (default: \"http://info.ruc.edu.cn/\")\n";
	getline(std::cin, domain);
	if (domain.empty()) domain = default_domain;
	std::cout << "Input root_url: (default: \"index.php\")\n";
	getline(std::cin, root_url);
	if (root_url.empty()) root_url = default_root_url;
	std::cout << "Input save_file_folder: (default: \"page/\")\n";
	getline(std::cin, save_file_folder);
	if (save_file_folder.empty()) save_file_folder = default_save_file_folder;

	gettimeofday(&start_time, NULL);
	int total_num = crawl(domain, root_url, save_file_folder, start_time);
	std::cout << "finished!  total: " << total_num << " pages" << std::endl;

	return 0;
}