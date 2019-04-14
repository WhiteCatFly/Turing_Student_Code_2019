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

Parser::Parser()
{
	cout << "please input the website and safe file's name" << endl;
	cin >> website >> name;
	string command = "touch " + name;
	system(command.data());
	download(website, name);
}

Parser::~Parser(){};

void Parser::set_type()
{
	cout << "choose parse type:\n1 : title\n2 : text\n3 : link\n4 : custom" << endl;
	cin >> type;
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
		cerr << "wrong parse type, please re-input parse type" << endl;
		set_type();
	}
	}
}

void Parser::analyze()
{
	string s, tmp;
	fstream fin(name.data(), ios::in);
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

void Parser::print()
{
	for (size_t i = 0; i < v.size(); i++)
		cout << v[i] << endl;
}