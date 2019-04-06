#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "download.h"
#include "find_append.h"
using namespace std;

int main()
{
	int counter = 0;
	string homepage;
	printf("input the homepage\n");
	cin >> homepage;
	regex regex_str_homepage(homepage);
	map<string, bool> mp;
	mp[homepage] = true;
	queue<string> q;
	q.push(homepage);
	if (system("find pages -type d") == 256)
		system("mkdir pages");
	while (!q.empty())
	{
		string now_page = q.front(), name = "pages/" + to_string(++counter);
		cout << "main now_page : " << now_page << endl; 
		q.pop();
		download(now_page, name);
		ifstream fin(name.data(), ios::in);
		append_finder af;
		af.find_append(q, mp, fin, now_page, regex_str_homepage);
	}
	return 0;
}