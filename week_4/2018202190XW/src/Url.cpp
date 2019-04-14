#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Url.h"
#include "StringModify.h"

bool operator < (const Url &lhs, const Url &rhs) {
	return lhs.path < rhs.path;
}
bool operator == (const Url &lhs, const Url &rhs) {
	return lhs.path == rhs.path;
}
Url::Url(std::string url) {
	const bool is_abs_path = parse_url(url);
	if (!is_abs_path) {
		std::cerr << "Invalid url" << url << std::endl;
		exit(0);
	}
	normalize();
	generate_path();
	generate_savepath();
}
Url::Url(std::string url, const Url &referer) {
	const bool is_abs_path = parse_url(url);
	if (protocol.empty() ^ protocol.empty()) {
		std::cerr << "Invalid url" << url << std::endl;
		exit(0);
	}
	if (protocol.empty()) {
		protocol = referer.protocol;
		host = referer.host;
	}
	if (!is_abs_path) {
		const size_t pos = referer.location.rfind('/');
		if (pos == std::string::npos) {
			std::cerr << "Invalid url" << url << std::endl;
			exit(0);
		}
		location = referer.location.substr(0, pos) + location;
	}
	normalize();
	generate_path();
	generate_savepath();
}
void Url::normalize() {
	std::vector<std::string> arr = split(location, '/');
	for (auto it = arr.begin(); it != arr.end(); ) {
		if (*it == ".") it = arr.erase(it);
		else if (*it == "..") {
			if (it != arr.begin()) {
				it--;
				it = arr.erase(it);
			}
			it = arr.erase(it);
		}
		else it++;
	}
	location = merge(arr, '/');
}
bool Url::parse_url(std::string url) {
	size_t pos;
	bool is_abs_path;
	if ((pos = url.rfind('#')) != std::string::npos) url = url.substr(0, pos - 1);
	static const std::regex my_regex("^(?:((?:[a-zA-Z0-9_]+:)?//)([a-zA-Z0-9\\.\\-@]+(?::\\d+)?))?((?:/.*)?)$");
	std::smatch match;
	if (std::regex_search((std::string &)url, match, my_regex)) {
        protocol = match[1];
		change_lower(protocol);

        host = match[2];
		change_lower(host);

        location = match[3];
        if (location.empty()) location = '/';
        is_abs_path = true;
    } else {
        location = url;
        is_abs_path = false;
	}
	parse_query();
	return is_abs_path;
}
void Url::parse_query() {
	size_t pos;
	if ((pos = location.find('?')) != std::string::npos) {
		query = location.substr(pos);
		location = location.substr(0, pos - 1);
	}
}
void Url::generate_path() {
	path = protocol + host + location + query;
}
void Url::generate_savepath() {
	savepath = path;
	std::replace(savepath.begin(), savepath.end(), '/', '_');
}