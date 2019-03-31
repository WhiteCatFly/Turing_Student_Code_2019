#include <string>

#include "StringModify.h"

std::string replace_sub_string(const std::string &str, const std::string old_s, const std::string new_s) {
	std::string ret_str;
	for (int i = 0; i < str.size(); i++) {
		if (i + old_s.size() <= str.size() && str.substr(i, old_s.size()) == old_s) {
			ret_str += new_s;
			i += old_s.size() - 1;
		}
		else ret_str += str[i];
	}
	return ret_str;
}

void replace_char(std::string &str, const char old_c, const char new_c) {
	for (auto &c : str) {
		if (c == old_c) c = new_c;
	}
}
std::string escape_url(const std::string &pre_url) {
	std::string ret_url;
	for (int i = 0; i < pre_url.size(); i++) {
		if (pre_url[i] == '&' || pre_url[i] == '(' || pre_url[i] == ')') {
			ret_url += '\\';
		}
		ret_url += pre_url[i];
	}
	return ret_url;
}
void modify_savepath(std::string &pre_url) {
	replace_char(pre_url, '/', '_');
}