#ifndef _GETCONTENT_H
#define _GETCONTENT_H

#include"cmdparser.h"
#include<string>

int FromStringToInt(const std::string &str);

class GetContent{
private:
    static int tries;
    static int timeout;
    static std::string filename;  //changable arguments
protected:
    std::string m_content;
    std::string m_url;
public:
    GetContent(){};
    ~GetContent(){};
    GetContent(const std::string &url) : GetContent(url, tries, timeout, filename) {}; //委托构造
    GetContent(const std::string &url, int _tries, int _timeout, const std::string &file_name); 
    GetContent(const CMDparser &cmd) : GetContent(cmd.url, FromStringToInt(cmd.tries), FromStringToInt(cmd.timeout), filename){}; //委托构造
    void show();
};

#endif