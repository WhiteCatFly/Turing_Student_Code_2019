#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <regex>
#include <set>
#include <map>
 
#include <unistd.h>

#include "Crawler.h"
#include "DOM.h"

#define _HTML ".html"
#define MKDIR_ORDER "mkdir -p "

extern std::string rootUrl;
extern std::string SAVE_PATH;

const std::string _HTTP = "http://";
const std::string _HTTPS = "https://";

extern int MAX_EASY_NUM;

extern std::ofstream flog;

Crawler::Crawler(std::string &root)
{
    num = 0;
    while(!waiting.empty()) 
        waiting.pop_front();
    urlStatus.clear();
    addUrl(root);
}

Crawler::Crawler(std::ifstream &fvisit_, std::ifstream &flog_, int &pageNum)
{
    num = 0;
    while(!waiting.empty())
        waiting.pop_front();

    std::string str;
    while(getline(fvisit_, str))
    {
        setSuccess(str);
        pageNum++;
    }
    while(getline(flog_, str))
        if(!isVisit(str))
            addUrl(str);
}

bool Crawler::isVisit(const std::string &url)
{
    return urlStatus[url] != STATUS_UNVIS; 
}

int Crawler::queryFailTime(const std::string url)
{
    if(urlStatus[url] == STATUS_OK)
        return 0;
    return urlStatus[url];
}

bool Crawler::queryFail(const std::string &url)
{
    return urlStatus[url] == STATUS_FAIL;
}

void Crawler::setSuccess(const std::string &url)
{
    urlStatus[url] = STATUS_OK;
}

void Crawler::setFail(const std::string &url)
{
    urlStatus[url] = STATUS_FAIL;
}

std::vector<std::string> Crawler::getNextBatch()
{
    std::vector<std::string> ret;
    ret.clear();
    int index = 0;
    while(index < MAX_EASY_NUM && !waiting.empty())
    {
        std::string tmp = waiting.front();
        ret.push_back(tmp);
        waiting.pop_front();
        index++;
        num--;
    }
    return ret;
}

void Crawler::addUrl(const std::string &url)
{
    if(urlStatus[url] != STATUS_OK && urlStatus[url] != STATUS_FAIL)
    {
        urlStatus[url]++;
        num++;
        waiting.push_back(url);
    }
}

// save content to file
void Crawler::setResponse(std::string url, std::string &content)
{
    if(content.empty())
        return;

    url = url.substr(rootUrl.length());
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

void Crawler::parseHTML(std::string &f_url, std::string &content)
{
    DOM DOMTree(content);
    std::vector<std::string> urlList = DOMTree.extractTagAttr("a", "href");
    for(auto &r : urlList)
    {
        std::string nextUrl = normalizeUrl(r, f_url);
        if(!nextUrl.empty() && !isVisit(nextUrl))
        {
            addUrl(nextUrl);
            flog << nextUrl << std::endl;
        }
    }
}

std::string normalizeUrl(std::string url, std::string &f_url)
{
    std::string emptyStr = "", ret;
    
    if(url[0] == '\'' || url[0] == '\"')
        url = url.substr(1);

    for(auto s : blackSubList)
    {
        if(url.find(s) != std::string::npos)
            return emptyStr; 
    }

    if(url.substr(0, rootUrl.size()) == rootUrl)
        return url;
   
    if(url.substr(0, _HTTP.size()) == _HTTP ||
       url.substr(0, _HTTPS.size()) == _HTTPS)
        return emptyStr;

    if(url[0] == '/')
        ret = rootUrl + url.substr(1);
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