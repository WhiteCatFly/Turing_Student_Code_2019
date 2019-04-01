#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <regex>

class Crawler
{
private:	
        std::string root;
        std::string save_path;
        std::queue<std::string> url_to_be_crawled;
        std::set<std::string> url_already_be_crawled;
        static int count;

        std::string GetPageToFile(const std::string url, const std::string path,int count);
        void ReadFile(const std::string file_name, const std::string path, std::string &content);
        void ParseOnePage(std::string &current_url, std::string &content, std::queue<std::string> &url_to_be_crawled);
public:
        Crawler();
        Crawler(const std::string url);
        Crawler(const std::string url, const std::string path);
        ~Crawler();

	void Core();
};


#endif
