#include "normal_url.h"

void normalize_url(string &url_name, string::size_type &index, const string &source_code, const string &web_name, const string &root_name)
{
	index += 8;
	string::size_type next_index = source_code.find('\"', index + 1);
	url_name = source_code.substr(index, next_index - index);
	index = next_index + 1;
	if (url_name.find("http://") == string::npos) {
		string temp = web_name;
		if (url_name[0] == '/') {
			temp = root_name;
		}
		else {
			string::size_type last_pos, last_index = temp.find('/', 22);
			last_pos = max (22, (int)last_index);
			while (last_index != string::npos) {
				last_pos = last_index;
				last_index = temp.find('/', last_pos + 1);
			}
			if (temp.find('.', last_pos + 1) != string::npos) {
				temp = temp.substr(0, last_pos);
			}
			while ((url_name[0] == '.' && url_name[1] == '.') || (url_name[0] == '.' && url_name[1] == '/') ) {
				if (url_name[1] == '/') {
					url_name = url_name.substr(2);
					continue;
				}	
				last_index = temp.find('/', 0);
				last_pos = last_index;
				while (last_index != string::npos) {
					last_pos = last_index;
					last_index = temp.find('/', last_pos + 1);
				}
				temp = temp.substr(0, last_pos);
				url_name =  url_name.substr(3);				
			}
			if (url_name[0] != '/') {
				temp.append("/");
			}
		}
		temp.append(url_name);
		url_name = temp;
	}
}
