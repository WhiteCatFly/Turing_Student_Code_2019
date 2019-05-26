#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using std::string;

class parser
{
    public:
    friend void string_replace(string &content,string &str,string &str_replace);
    
    parser(){}
    parser(char* file)
    {
        fout_result.open(file);
    }
    void set_fout(std::string file = "result.txt")
    {
        fout_result.open(file);
    }
    void get_title(string content);
    void get_body(string content);
    void get_type(string &type,string content);
    int  if_get_urls(string str,std::string current,std::string root,std::string &record_str);

    void judge_mark(std::string &str);
    void judge_jump(std::string &str);
    ~parser(){}

    private:
    std::ofstream fout_result;

};

#endif