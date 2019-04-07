#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <regex>
#include <set>
#include <map>
 
#include <unistd.h>

#include "my_crawler.h"

#define _HTML ".html"
#define MKDIR_ORDER "mkdir -p "

#define _PREFIX 5

extern std::string root_url;
extern std::string SAVE_PATH;

const std::string _HTTP = "http://";
const std::string _HTTPS = "https://";
const std::regex re_href("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");

extern int MAX_EASY_NUM;


void my_crawler::init(std::string &root)
{
    num = 0;
    while(!waiting.empty()) 
        waiting.pop();
    url_status.clear();

    add_url(root);
}

bool my_crawler::is_visit(const std::string &url)
{
    return url_status[url] != STATUS_UNVIS; 
}

int my_crawler::query_fail_time(const std::string &url)
{
    if(url_status[url] == STATUS_OK)
        return 0;
    return url_status[url];
}

bool my_crawler::query_fail(const std::string &url)
{
    return url_status[url] == STATUS_FAIL;
}

void my_crawler::set_success(const std::string &url)
{
    url_status[url] = STATUS_OK;
}

void my_crawler::set_fail(const std::string &url)
{
    url_status[url] = STATUS_FAIL;
}


std::vector<std::string> my_crawler::get_next_batch()
{
    std::vector<std::string> ret;
    ret.clear();
    int index = 0;
    while(index < MAX_EASY_NUM && !waiting.empty())
    {
        std::string tmp = waiting.front();
        ret.push_back(tmp);
        waiting.pop();
        index++;
        num--;
    }
    return ret;
}

void my_crawler::add_url(const std::string &url)
{
    if(url_status[url] != STATUS_OK && url_status[url] != STATUS_FAIL)
    {
        url_status[url]++;
        num++;
        waiting.push(url);
    }
}

// save content to file
void my_crawler::set_response(std::string url, std::string &content)
{
    if(content.empty())
        return;

    url = url.substr(root_url.length());
    if(url[url.size() - 1] == '/' || url.empty())
        url = url + "index";
    
    std::size_t found = url.find_last_of('/');
    std::string path = SAVE_PATH + url.substr(0, found + 1);
    std::string order = MKDIR_ORDER + path;

    if(access(path.c_str(), 0) == -1)
        system(order.c_str());

    std::ofstream fw;
    fw.open((SAVE_PATH + url + _HTML).c_str());
    fw << content;
    fw.close();
}

void my_crawler::parse_html(std::string &f_url, std::string &content)
{
    std::sregex_iterator it(content.begin(), content.end(), re_href), end;
    for(; it != end; it++)
    {
        std::string next_url = normalize_url(it->str(), f_url);
        if(!next_url.empty() && !is_visit(next_url))
            add_url(next_url);
    }
}

// "href=......"-> root_url + path 
std::string normalize_url(std::string url, std::string &f_url)
{
    std::string empty_str = "", ret;
    
    url = url.substr(_PREFIX, url.size() - _PREFIX - 1);
    
    if(url[0] == '\'' || url[0] == '\"')
        url = url.substr(1);


    for(auto s : black_sub_list)
    {
        if(url.find(s) != std::string::npos)
            return empty_str; 
    }

    if(url.substr(0, root_url.size()) == root_url)
        return url;
   
    if(url.substr(0, _HTTP.size()) == _HTTP ||
       url.substr(0, _HTTPS.size()) == _HTTPS)
        return empty_str;


    if(url[0] == '/')
        ret = root_url + url.substr(1);
    else
    {
        size_t found = f_url.find_last_of('/');
        ret = f_url.substr(0, found + 1) + url;
    }


    // 处理 /../
    int pos;

    while((pos = ret.find("..")) != std::string::npos)
    {
        int pre = pos - 2;
        while(pre > 0 && ret[pre] != '/') 
            pre--;
        pos++;
        // aaaa/bbbbbb/ccccc/../dd
        //            .pre    .pos

        ret = ret.erase(pre, pos - pre + 1);
    }

    // 处理 /./
    while((pos = ret.find("/./")) != std::string::npos)
    {
        ret = ret.erase(pos, 2);
    }


    // 处理 #
    if((pos = ret.find('#')) != std::string::npos)
    {
        ret = ret.substr(0, pos);
    }

    return ret;
}