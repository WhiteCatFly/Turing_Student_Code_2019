#ifndef HTMLPARSER_H_INCLUDED
#define HTMLPARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <regex>
#include <algorithm>
#include <cstdlib>
#include <set>
const int MAX = 20;
const int MaxWebUrl = 300;
const char BlackList[][MAX] = {".doc" , ".pdf" , ".xls" , "@" , ".css" , "/en/"};
class Parser
{
private:
    std::string website;
    std::string page_content;
    std::set <std::string> url_already_saved;
    std::string prefixion;
    void SetUrl();
    bool BlackListCheck(std::string url);
    bool JudgeReOrAb(std::string url);
    void RelativeSite(std::string url);
    void AbsoluteSite(std::string url);
public:
    Parser(std::stringstream str,std::string website_);
    Parser(const char*filename,std::string website_);
    Parser() = default;
    ~Parser();

    void Title();
    void Body();
    void Url();
};

#endif
