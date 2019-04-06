#include "crawler.h"

crawler::crawler() {}

crawler::crawler(string str, string storename)
{
	this->start_name = str.c_str();
	this->storename = storename.c_str();
}

crawler::~crawler() {}

void crawler::_get_url()
{
	set <string> vis;
	queue <string> q;
	vis.insert(this->start_name);
	q.push(this->start_name);
	while(!q.empty()) {
		string web_name = q.front();
		q.pop();
		string pre = web_name.substr(0, 22);
		if (pre != this->start_name)
			break;
		string source_code = get_source_code(web_name);
		string::size_type index = 0;
		while(index < source_code.size()) {
			index = source_code.find("a href=\"", index);
			if (index == string::npos)
				break;
			string url_name;
			normalize_url(url_name, index, source_code, web_name, this->start_name);
			if (url_name.find("@") != string::npos || url_name.find("javascript") != string::npos)
				continue;
			if (!vis.count(url_name)) {
				vis.insert(url_name);
				q.push(url_name);
			}
		}
	}
}
