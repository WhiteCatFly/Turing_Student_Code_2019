#include "crawler.h"

void _get_url()
{
	string start_name = "http://info.ruc.edu.cn";
	set <string> vis;
	queue <string> q;
	vis.insert(start_name);
	q.push(start_name);
	while(!q.empty()) {
		string web_name = q.front();
		q.pop();
		string pre = web_name.substr(0, 22);
		if (pre != start_name)
			break;
		string source_code = get_source_code(web_name);
		string::size_type index = 0;
		while(index < source_code.size()) {
			index = source_code.find("a href=\"", index);
			if (index == string::npos)
				break;
			string url_name;
			normalize_url(url_name, index, source_code, web_name);
			if (!vis.count(url_name)) {
				vis.insert(url_name);
				q.push(url_name);
			}
		}
	}
}
