#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "UrlParser.h"
#include "StringModify.h"

std::string normalize(const std::string &domain, const std::string &current_url, std::string pre_url) {
	if (pre_url.find("https") != std::string::npos) return "";
	size_t pos;
	if ((pos = pre_url.find("http://")) != std::string::npos) {
		pos = pre_url.find(domain);
		if (pos != std::string::npos) {
			pre_url.erase(pos, domain.size());
		}
		else return "";
	}
	else if (pre_url[0] == '/') {
		pre_url.erase(pre_url.begin());
	}
	else {
		if ((pos = current_url.rfind('/')) != std::string::npos) {
			pre_url = current_url.substr(0, pos + 1) + pre_url;
		}
	}
	if ((pos = pre_url.find('#')) != std::string::npos) {
		pre_url.erase(pos, pre_url.size() - pos);
	}
	if (pre_url.size() == 0) return "";
	if (pre_url.find('.') != std::string::npos) {
		if (pre_url.find("html") == std::string::npos && pre_url.find("php") == std::string::npos) {
			return "";
		}
		else return pre_url;
	}
	else {
		if (pre_url[pre_url.size() - 1] == '/') return pre_url + "index.php";
		else return pre_url + "/index.php";
	}
}
void extract_url(const std::string &domain, const std::string &current_url, const std::string &savepath, std::vector<std::string> &target) {
	std::vector<std::string> ret;
	std::string current_content;
	std::ifstream ifstrm(savepath);
	const std::regex my_regex("<a[^<>]*?href=\"([^@]*?)\"[^<>]*?>");
	while (getline(ifstrm, current_content)) {
		std::smatch res;
		while (std::regex_search(current_content, res, my_regex)) {
			std::string new_url = res[1].str();
			new_url = replace_sub_string(new_url, "&amp;", "&");
			new_url = normalize(domain, current_url, new_url);
			target.push_back(new_url);
			current_content = res.suffix();
		}
	}
}