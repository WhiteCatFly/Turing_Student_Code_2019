#include "detail_parser.h"

string gettime()
{
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

void print_log(string web_name, string par_type)
{
	ofstream fp("log");
	fp << gettime() << "	" << "craw " << web_name << par_type << " success!" << endl;
}

void title_parser::get_title(string file_name)
{
	set <string> vis;
	queue <string> q;
	vis.insert(web_name);
	q.push(web_name);
	while(!q.empty()) {
		string _web_name = q.front();
		q.pop();
		string pre = _web_name.substr(0, 22);
		if (pre != web_name)
			break;
		string source_code = get_source_code(_web_name);
		source_str = source_code;
		int index = source_str.find("<title>") + 7;
		int len = source_str.find("</title>") - index;
		string title = source_str.substr(index, len);
		ofstream fp(file_name.c_str());
		fp << title;
		string::size_type _index = 0;
		while(_index < source_code.size()) {
			_index = source_code.find("a href=\"", _index);
			if (_index == string::npos)
				break;
			string url_name;
			normalize_url(url_name, _index, source_code, _web_name, web_name);
			if (url_name.find("@") != string::npos || url_name.find("javascript") != string::npos)
				continue;
			if (!vis.count(url_name)) {
				vis.insert(url_name);
				q.push(url_name);
			}
		}
		print_log(_web_name, "title");
	}
}

void passage_parser::get_passage(string file_name)
{
	set <string> vis;
	queue <string> q;
	vis.insert(web_name);
	q.push(web_name);
	while(!q.empty()) {
		string _web_name = q.front();
		q.pop();
		string pre = _web_name.substr(0, 22);
		if (pre != web_name)
			break;
		string source_code = get_source_code(_web_name);
		source_str = source_code;
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
		string::size_type _index = 0;
		while(_index < source_code.size()) {
			_index = source_code.find("a href=\"", _index);
			if (_index == string::npos)
				break;
			string url_name;
			normalize_url(url_name, _index, source_code, _web_name, web_name);
			if (url_name.find("@") != string::npos || url_name.find("javascript") != string::npos)
				continue;
			if (!vis.count(url_name)) {
				vis.insert(url_name);
				q.push(url_name);
			}
		}
		print_log(_web_name, "title");
	}
}

void url_parser::get_url(string file_name)
{
	set <string> vis;
	queue <string> q;
	vis.insert(web_name);
	q.push(web_name);
	while(!q.empty()) {
		string _web_name = q.front();
		q.pop();
		string pre = _web_name.substr(0, 22);
		if (pre != web_name)
			break;
		string source_code = get_source_code(_web_name);
		source_str = source_code;
		string::size_type _index = 0;
		while(_index < source_code.size()) {
			_index = source_code.find("a href=\"", _index);
			if (_index == string::npos)
				break;
			string url_name;
			normalize_url(url_name, _index, source_code, _web_name, web_name);
			if (url_name.find("@") != string::npos || url_name.find("javascript") != string::npos)
				continue;
			ofstream fp(file_name.c_str());
			fp << url_name << endl;
			if (!vis.count(url_name)) {
				vis.insert(url_name);
				q.push(url_name);
			}
		}
		print_log(_web_name, "title");
	}
}
