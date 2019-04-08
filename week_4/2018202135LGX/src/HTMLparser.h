#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<regex>
#include<sstream>
#include<set>

class HTMLparser{
private:
    std::string web_content;
    std::string title;
    std::string body;
    std::string host;
    std::set<std::string> Img;
public:
    HTMLparser(std::string url);
    HTMLparser(std::ifstream fin);
    void GetTitle();
    void GetBody();
    void GetImg();
    std::string trans_URLs(std::string aurl);
    std::string trans_URLs_for_Img(std::string aurl);
};

std::string GetContent(std::string url);

std::string RemoveTag(std::string str);

std::string get_title(std::string str);

std::string get_title_1(std::string str);

#endif