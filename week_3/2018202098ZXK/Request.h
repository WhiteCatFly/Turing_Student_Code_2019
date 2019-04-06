#ifndef SPIDER_REQUEST_
#define SPIDER_REQUEST_
#include <regex>
#include <string>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>

#include "string_tools.h"

using std::string;


struct Config
{
	string BASE;
	string err_file;
	bool loaded;
	int thread_num;
	int sleep_time;
	int tries_num;
	int time_out;
	
};
Config iniConfig(const string& iniFile);

class Request
{
private:
	string url;
	string filename;
	string cur_dir; //current url directory.
	bool crawled; //it will be true if and only if this url is successfully crawled
	static string BASE;
	static int time_out;
	static int tries_num;
public:
	Request(){}
	Request(string url_);
	bool parseUrl(string &s_url);
	void crawl();
	void getUrls(std::vector<string> &v);
	bool getStatus(){return crawled;}
	~Request(){}
	static void set_config(Config &conf);
};
#endif