#ifndef _HTMLPASER_H
#define _HTMLPASER_H

#include"GetContent.h"
#include<queue>


class HTMLparser: private GetContent{ // 使用继承
friend class Crawler; // 友元类
private:
    enum htmltype{FINE_HTML, BAD_HTML, NOT_A_HTML}; // 用于检测网站可用性， 为提供断点重爬功能
    htmltype m_htmltype;
    bool m_valid;
public:
    void urlparser(std::queue<std::string>&aqueue); // 将当前页面下的所有路径改为相对路径，并放入传入的双端队列中
    HTMLparser(const CMDparser&other); //从一个命令构造，用于爬虫的初始化
    HTMLparser(const std::string&url); //从url构造，实现爬虫bfs算法获取网页的功能
    ~HTMLparser(){};
    HTMLparser(){};
    bool Valid(){ return m_valid;};
};

#endif