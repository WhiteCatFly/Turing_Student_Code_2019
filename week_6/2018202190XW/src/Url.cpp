#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Url.h"
#include "StringModify.h"

bool operator < (const Url &lhs, const Url &rhs) {
	return lhs.path < rhs.path;
}
bool operator == (const Url &lhs, const Url &rhs) {
	return lhs.path == rhs.path;
}

std::string Url::get_savepath() const{
	std::string ret_value = path;
	replace_char(ret_value, '/', '_');
	return ret_value;
}
size_t Url::rfind(const char &c) const{
	return path.rfind(c);
}
std::string Url::substr(size_t from_pos, size_t length) const{
	return path.substr(from_pos, length);
}
bool Url::empty() const{
	return path.empty();
}

void Url::normalize(const std::string referer) {
	size_t pos, domain_pos;
	domain_pos = referer.find('/', 8);
	std::string domain = referer.substr(0, domain_pos);
	if ((pos = path.find("http")) != std::string::npos) {
		pos = path.find(domain);
		if (pos == std::string::npos) {
			path = "";
			return;
		}
	}
	else if (path[0] == '/') {
		path = domain + path;
	}
	else {
		if ((pos = referer.rfind('/')) != std::string::npos) {
			path = referer.substr(0, pos + 1) + path;
		}
	}
	while (path[0] == '/') path.erase(path.begin());
	if ((pos = path.find('#')) != std::string::npos) {
		path.erase(pos, path.size() - pos);
	}
	if (path.size() == 0) {
		path = "";
		return;
	}
	pos = 0;
	while ((pos = path.find("./", pos)) != std::string::npos) {
		if (pos == 0 || path[pos - 1] != '.') path.erase(pos, 2);
		else pos += 2;
	}
	pos = 0;
	while ((pos = path.find("/../", pos)) != std::string::npos) {
		if (pos != 0) {
			size_t tmp_pos;
			if ((tmp_pos = path.rfind('/', pos - 1)) != std::string::npos) {
				path.erase(path.begin() + tmp_pos, path.begin() + pos + 4);
			}
			else path.erase(path.begin(), path.begin() + pos + 4);
		}
		else pos += 3;
	}
	if (path.find('.', domain_pos) != std::string::npos) {
		if (path.find("html") == std::string::npos && path.find("php") == std::string::npos &&
			path.find("asp") == std::string::npos) {
			path = "";
			return;
		}
	}
	else {
		if (path[path.size() - 1] != '/') path = path + "/";
	}
}