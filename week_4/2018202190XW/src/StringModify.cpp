#include <string>
#include <cctype>
#include <vector>

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

void change_lower(std::string str) {
	for (auto &c : str) if (isupper(c)) c = c - 'A' + 'a'; 
}
void escape_blank(std::string &str) {
	std::string ret;
	for (auto c : str) {
		switch (c) {
			case '\n':
				ret += "\\n";
				break;
			case '\r':
				ret += "\\r";
				break;
			case '\t':
				ret += "\\t";
				break;
			default:
				ret += c;
				break;
		}
	}
	str = ret;
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

std::vector<std::string> split(std::string str, char seperator) {
	std::vector<std::string> ret_value;
	size_t start_pos = 0, pos;
	while ((pos = str.find(seperator, start_pos)) != std::string::npos) {
		if (pos > start_pos) ret_value.push_back(str.substr(start_pos, pos - start_pos));
		start_pos = pos + 1;
	}
	if (pos < str.size()) ret_value.push_back(str.substr(pos));
	return ret_value;
}

std::string merge(std::vector<std::string> &arr, char seperator) {
	std::string ret_value;
	for (auto s : arr) ret_value += s + seperator;
	return ret_value;
}