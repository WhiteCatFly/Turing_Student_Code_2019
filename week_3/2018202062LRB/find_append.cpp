#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "find_append.h"
#include "normalize.h"
using namespace std;

append_finder::append_finder()
{	
	regex_str = "a href=['\"]?[^'\"@> ]+['\"> ]?";
}

append_finder::~append_finder()
{
}

void append_finder::find_append(queue<string> &q, map<string, bool> &mp, ifstream &fin, const string now_page, const regex regex_str_homepage)
{
	string tmp;
	while (getline(fin, tmp))
	{
		string::const_iterator iterStart = tmp.begin();
		string::const_iterator iterEnd = tmp.end();
		while (regex_search(iterStart, iterEnd, result, regex_str))
		{
			string next_page = normalizing(now_page, result[0]);
			if (regex_search(next_page, regex_str_homepage))
			{
				if (!mp[next_page])
				{
					cout << "next_page : " << next_page << endl; 
					mp[next_page] = true;
					q.push(next_page);
				}
			}
			iterStart = result[0].second;
		}
	}
}