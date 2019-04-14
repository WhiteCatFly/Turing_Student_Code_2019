#include "html_parser.h"

void html_parser::get_title(string file_name)
{
	int index = source_str.find("<title>") + 7;
	int len = source_str.find("</title>") - index;
	string title = source_str.substr(index, len);
	ofstream fp(file_name.c_str());
	fp << title;
}

void html_parser::get_passage(string file_name)
{
	int index = 0, len;
	ofstream fp(file_name.c_str());
	while ( (string::size_type)(index = source_str.find("<p>", index) ) != string::npos) {
		index += 3;
		len = source_str.find("</p>", index) - index;
		string p = source_str.substr(index, len);
		int space_index = 0;
		while ( (string::size_type)(space_index = p.find("&nbsp;", space_index)) != string::npos) {
			p.replace(space_index, 6, " ");
			space_index += 6;
		}
		index += len;
		fp << '\t' << p << endl;
	}
}

void html_parser::get_url(string file_name, string web_name)
{
	string::size_type index = 0;
	int start_len = web_name.find("/", 7);
	string start_name = web_name.substr(0, start_len);
	ofstream fp(file_name.c_str());
	while(index < this->source_str.size()) {
		index = this->source_str.find("a href=\"", index);
		if (index == string::npos)
			break;
		string url_name;
		normalize_url(url_name, index, this->source_str, web_name, start_name);
		if (url_name.find("@") != string::npos || url_name.find("javascript") != string::npos)
			continue;
		fp << url_name << endl;
	}
}
