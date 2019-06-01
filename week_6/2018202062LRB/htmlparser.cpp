#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <vector>
#include "download.h"
#include "htmlparser.h"
#include "normalize.h"
using namespace std;

Parser::Parser(){};

Parser::Parser(string website_, int type_, string name_, bool toparse_, bool tocrawl_)
{
	website = website_;
	type = type_;
	name = name_;
	toparse = toparse_;
	tocrawl = tocrawl_;
	system("mkdir website");
	string command = "touch " + name;
	system(command.data());
}

void Parser::init(string website_, int type_, string name_, bool toparse_, bool tocrawl_)
{
	website = website_;
	type = type_;
	name = name_;
	toparse = toparse_;
	tocrawl = tocrawl_;
	system("mkdir website");
	string command = "touch " + name;
	system(command.data());
	download(website, "website/" + filename(website));
}

Parser::~Parser(){};

bool Parser::set_type()
{
	switch (type)
	{
	case 1 : 
	{
		regex_str = "<title>.+?</title>";
		break;
	}
	case 2 :
	{
		regex_str = "<p(.+?){0,1}>.+?</p>";
		break;
	}
	case 3 :
	{
		regex_str = "a href=['\"]?[^'\"@> ]+['\"> ]?";
		break;
	}
	case 4 :
	{
		printf("input the regex : ");
		string s;
		cin >> s;
		regex_str = s;
		puts("");
		break;
	}
	default :
	{
		cerr << "wrong parse type, please re-input parse type: 1 ~ 4" << endl;
		return false;
	}
	}
	return true;
}

void Parser::parse()
{
	if (!toparse)
		return;
	string s, tmp;
	download(website, "website/" + filename(website));
	fstream fin(("website/" + filename(website)).data(), ios::in);
	while (getline(fin, tmp))
		s += tmp;
	string::const_iterator iterStart = s.begin();
	string::const_iterator iterEnd = s.end();
	while (regex_search(iterStart, iterEnd, result, regex_str))
	{
		v.push_back(normalizing(website, result[0], type));
		iterStart = result[0].second;
	}
}

void Parser::find_append(const string now_page)
{
	string s, tmp;
	download(now_page, "website/" + filename(now_page));
	fstream fin(("website/" + filename(now_page)).data(), ios::in);
	while (getline(fin, tmp))
		s += tmp;
	string::const_iterator iterStart = s.begin();
	string::const_iterator iterEnd = s.end();
	while (regex_search(iterStart, iterEnd, result, regex_str))
	{
		string next_page = normalizing(now_page, result[0], 3);
		if (regex_search(next_page, regex(website)))
		{
			if (!mp[next_page])
			{
				mp[next_page] = true;
				q.push(next_page);
			}
		}
		iterStart = result[0].second;
	}
}

void Parser::crawl()
{
	if (!tocrawl)
		return;
	q.push(website);
	while (!q.empty())
	{
		find_append(q.front());
		q.pop();
	}
}

void Parser::print_parser()
{
	if (!toparse)
		return;
	fstream fout(name.data(), ios::out);
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
		fout << v[i];
	}
}

void Parser::print_crawler()
{
	if (!tocrawl)
		return;
	for (map<string, bool>::iterator i = mp.begin(); i != mp.end(); i++)
		cout << i->first << endl;
}