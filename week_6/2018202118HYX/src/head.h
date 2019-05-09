#ifndef HEAD_H
#define HEAD_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <queue>
#include <regex>
#include <set>

class Get
{
private:
    std::string url;
public:
    Get();
    Get(std::string url_);
    virtual ~Get();
    virtual void getcontent(std::string& content,int n);
};

class Base
{
private:
    std::string root;
protected:
    int n;
    std::string current;
    std::queue<std::string> todo;
    std::set<std::string> done;

    int adjust(std::string &url);
    void parse(std::string& content,std::set<std::string>& urls);
public:
    Base();
    Base(std::string root_);
    virtual ~Base();

    virtual void BFS();
};

class Econ final:public Base
{
private:
    std::string econ;
public:
    Econ();
    ~Econ();
    void BFS();
};

class Info final:public Base
{
private:
    std::string info;
public:
    Info();
    ~Info();
    void BFS();
};

class Parser
{
private:
    std::string target;
    std::string content;
    std::string file;
    void getcontent();
public:
    Parser();
    Parser(std::string target_);
    ~Parser();

    void extract_title();
    void extract_content();
    void extract_url();
};

#endif