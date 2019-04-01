#include <bits/stdc++.h>

#define MAX_STR 1024

using namespace std;


string storename = "websource";

string get_source_code(string webname)
{
	string comm = "wget -q ";
	comm.append("\"");
	comm.append(webname);
	comm.append("\"");
	comm.append(" -O ");
	comm.append(storename);
	system(comm.c_str());
	cout <<webname <<endl;
	ifstream fp(storename.c_str());
	if (!fp)
		return "";
	string source_code;
	char temp[MAX_STR] = {0};
	while (fp.getline(temp, MAX_STR)) {
		source_code.append(string(temp));
		memset(temp, 0, sizeof(temp));
	}
	return source_code;
}

set <string> vis;
queue <string> q;

void get_url(string start_name)
{
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
			index += 8;
			string::size_type next_index = source_code.find('\"', index + 1);
			string url_name = source_code.substr(index, next_index - index);
			index = next_index + 1;
			if (url_name.find("http://") == string::npos) {
				string temp = web_name;
				while (url_name[0]=='.' && url_name[1]=='.') {
					string::size_type last_pos, last_index = temp.find('/', 0);
					last_pos = last_index;
					while (last_index != string::npos) {
						last_pos = last_index;
						last_index = temp.find('/', last_pos + 1);
					}
					temp = temp.substr(0, last_pos - 1);
					url_name =  url_name.substr(2);					
				}
				string::size_type last_pos, last_index = temp.find('/', 22);
				last_pos = max (22, (int)last_index);
				while (last_index != string::npos) {
					last_pos = last_index;
					last_index = temp.find('/', last_pos + 1);
				}
				if (temp.find('.', last_pos + 1) != string::npos) {
					temp = temp.substr(0, last_pos);
				}
				if (url_name[0] != '/') {
					temp.append("/");
				}
				temp.append(url_name);
				url_name = temp;
			}
			if (!vis.count(url_name)) {
				vis.insert(url_name);
				q.push(url_name);
			}
		}
	}
}

int main()
{
	freopen("crawler.out", "w", stdout);
	string webname = "http://info.ruc.edu.cn";
	vis.insert(webname);
	q.push(webname);
	get_url(webname);
	return 0;
}
