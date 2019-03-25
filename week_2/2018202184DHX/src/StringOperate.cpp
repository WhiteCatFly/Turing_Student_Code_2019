#include"StringOperate.h"
bool BlackListCheck(std::string url)
{
    for(int i = 0 ; i < sizeof(BlackList) / MAX ; i++)
    {
        if(url.find(BlackList[i],0) != url.npos)
        {
            return false;
        }
    }
    return true;
};

bool JudgeReOrAb(std::string url)
{
    if(url.find("http:\/\/",0) != url.npos)
    return true;
    else
    {
        return false;
    }
};

void RelativeSite(std::string url)
{
    std::string tempo;
    tempo.clear();
    if(url.find(".php",0) != url.npos)
    {
        if(*url.begin() == '/')    
        {
            tempo = Title + url;
        }
        else
        {
            tempo = Title + '/' + url;
        }
        if(url_already_crawled.find(tempo) == url_already_crawled.end())
        {
            url_to_be_crawled.push(tempo);
            url_already_crawled.insert(tempo);
        }
    }
    else if(url.find(".html",0) != url.npos)
    {
        if(*url.begin() == '/')    
        {
            tempo = Title + url;
        }
        else
        {
            tempo = Title + '/' + url;
        }
        if(url_already_crawled.find(tempo) == url_already_crawled.end())
        {
            url_to_be_crawled.push(tempo);
            url_already_crawled.insert(tempo);
        }
    }
    else if(url.find('.',0) == url.npos)
    {
        if(*url.begin() == '/')    
        {
                tempo = Title + url;
        }
        else
        {
            tempo = Title + '/' + url;
        }
        if(url_already_crawled.find(tempo) == url_already_crawled.end())
        {
            url_to_be_crawled.push(tempo);
            url_already_crawled.insert(tempo);
        }
    }
    return;
};

void AbsoluteSite(std::string url)
{
    if(url.find("http:\/\/",0) != url.npos)          
    {
        url.erase(url.begin(),url.begin() + 7);
        if(url.find(Title,0) != url.npos)
        {
            if(url_already_crawled.find(url) == url_already_crawled.end())
            {
                url_to_be_crawled.push(url);
                url_already_crawled.insert(url);
            }
        }
    }
    return;
};