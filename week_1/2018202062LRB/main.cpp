#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
using namespace std;

map<string, bool> mp;
queue<string> q;

string normalizing(string root, string append)
{
	root = root.substr(0, root.rfind("/"));
	append = append.substr(8);
	append.pop_back();
	while (append[0] == '.')
	{
		root = root.substr(0, root.rfind("/"));
		append = append.substr(3);
	}
	if (append[0] == 'h') return append;
	else return root + "/" + append;
}

int main()
{
	int counter = 0;
	regex regex_str("a href=\"[^\"@]+[^(doc|docx|xls|pdf|rar|zip)]\"");
	regex regex_str_website("http://info.ruc.edu.cn/");
	string index = "http://info.ruc.edu.cn/";
	mp[index] = true;
	q.push(index);
	while (!q.empty())
	{
		string now_page = q.front();
		q.pop();
		string tmp = "wget -O pages/" + to_string(++counter) + " " + now_page;
		system(tmp.data());
		tmp = "pages/" + to_string(counter);
		ifstream fin(tmp.data(), ios::in);
		smatch result;
		while (getline(fin, tmp))
		{
			string::const_iterator iterStart = tmp.begin();
			string::const_iterator iterEnd = tmp.end();
			while (regex_search(iterStart, iterEnd, result, regex_str))
			{
				string next_page = normalizing(now_page, result[0]);
				if (regex_search(next_page, regex_str_website))
				{
					//cout << next_page << endl;
					if (!mp[next_page])
					{
						mp[next_page] = true;
						q.push(next_page);
					}
				}
				iterStart = result[0].second;
			}
		}
	}
	return 0;
}