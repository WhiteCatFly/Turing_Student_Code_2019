#ifndef PARSER
#define PARSER

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <regex>
#include <algorithm>
#include <regex>
#include <stack>
#include <set>
#include <vector>

class Parser{
private:
    std::string Source_Code;
    static std::set<std::string> Label_Key;
    static std::string Big_Small_Same(std::string s);
    void Output(const std::string &code, int tabs, std::ostringstream &ostr);
    void Process();
public:
    Parser(const char *filename);
    Parser(const std::string &code);
    Parser() = default;
    int Extract(const std::regex &reg, std::vector<std::string> &result);
    int Get_Title(std::vector<std::string> &result);
    int Get_Body(std::vector<std::string> &result);
    int Get_Href(std::vector<std::string> &result);
    int Get_Img(std::vector<std::string> &result);
};

#endif
