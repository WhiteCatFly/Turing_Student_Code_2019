#ifndef HEAD_H
#define HEAD_H

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<regex>
#include<set>
using namespace std;

class parse_url
{
private:
    string current_url;
    string content;
    string root;

    int match(string url) const;
    int ifadjust( ) const;
    string adjust(string url);
public:
    parse_url()=default;
    parse_url(string &current_url_,string &root_);
    ~parse_url();
    void get_content(int &total);
    void parse(set<string> &urls);
};

#endif