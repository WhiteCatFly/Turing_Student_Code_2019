#include <set>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/time.h>

#include "Url.h"
#include "TagNode.h"
#include "Html.h"
#include "Crawler.h"


int main(int argc, char *argv[]) {
	const Url DEFAULT_ROOT_URL("http://info.ruc.edu.cn/");
	const std::string DEFAULT_DOWNLOAD_PATH = "page/";
	const std::string DEFAULT_SAVE_FILE_PATH = "crawl.save";
	bool has_save_file_path = false, has_load_path = false;
	bool has_root_url = false, has_download_path = false;
	std::string save_file_path, load_path, download_path;
	Url root_url;
	if (argc == 2 && ((std::string)argv[1] == "-h" || (std::string)argv[1] == "-help")) {
		std::cout << "-u <url>\tSet the root url to crawl\n\t\t"
		<< "DEFAULT=http://info.ruc.edu.cn/\n\n"
		<< "-s <path>\tSet the path to save save_file\n\t\t"
		<< "DEFAULT=crawl.save\n\n"
		<< "-load <path>\tContinue crawling with the save_file\n\n"
		<< "-o <path>\tRedirection web page save location\n\t\t"
		<< "DEFAULT=page/\n";
		return 0;
	}
	for (int i = 1; i + 1 < argc; i++) {
		if ((std::string)argv[i] == "-u") {
			has_root_url = true;
			root_url = Url(argv[i + 1]);
		}
		if ((std::string)argv[i] == "-load") {
			has_load_path = true;
			load_path = argv[i + 1];
		}
		if ((std::string)argv[i] == "-s") {
			has_save_file_path = true;
			save_file_path = argv[i + 1];
		}
		if ((std::string)argv[i] == "-o") {
			has_download_path = true;
			download_path = argv[i + 1];
		}
	}
	if (!has_root_url) {
		has_root_url = true;
		root_url = DEFAULT_ROOT_URL;
	}
	if (!has_save_file_path) {
		if (has_load_path) save_file_path = load_path;
		else save_file_path = DEFAULT_SAVE_FILE_PATH;
	}
	if (!has_download_path) download_path = DEFAULT_DOWNLOAD_PATH;

	int total_num;

	if (has_load_path) {
		Crawler crawler(load_path, download_path, save_file_path);
		total_num = crawler.crawl();
	}
	else if (has_root_url) {
		Crawler crawler(root_url, download_path, save_file_path);
		total_num = crawler.crawl();
	}
	
	std::cout << "finished!  total: " << total_num << " pages" << std::endl;
	return 0;
}