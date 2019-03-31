#ifndef TOOLS_H
#define TOOLS_H

#include <algorithm>
#include <vector>
#include <regex>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <ctime>

class get
{
    public:
     get()
    {
     total_urls=0;
    }

     get(std::string str,int number = 0)
    {   
     total_urls = number;
     current = str;
    }
    void get_path(std::string path)       //改变默认的sterage_path
    {
        storage_path = path;
    }
    void set_current(std::string str)
    {
        current = str;
    }
    std::string get_content();
    int get_num() const         //获得url的总数
    {
        return total_urls;
    }
    ~get()
    {

    }

    private:

     int total_urls;
     std::string current;
     std::string storage_path = "/home/halcyon/index.html";
//std::string storage_path;

};

class search;
class work
{   
    public:
    //friend class search;
    friend void if_find(work & work, search & search);
     work()
     {

     }
     work(std::string &current_,std::string &content_,std::string &root_)
     {
         current = current_;
         content = content_;
         root = root_;
     }
     void set(std::string &current_, std::string &content_,std::string &root_)
     {
         current = current_;
         content = content_;
         root = root_;
     }

     void parse();
     void judge(std::string str_,int mark);
     void judge_slash();
     void judge_mark();
     ~work()
     {

     }
     //void judge_jump(std::string str_);
     

    private:
     std::string current;
     std::string content;
     std::string str;
     std::string root;
     std::set <std::string> urls_tobe_judged;


};

class search
{
    
    public:
    friend class get;
    friend class work;
    friend void if_find(work & work,search & search);
    search()
    {

    }
    search(std::string root_)
    {
        urls_tobe_clawed.push(root_);
        root = root_;
    }
    
    void bfs(get & get, work & work, search & search);
    //void if_find();
    ~search()
    {

    }


    private:
    
    std::queue <std::string> urls_tobe_clawed;
    std::set   <std::string> urls_clawed;
    std::string root;
    std::ofstream fout;
    
    
};

void if_find(work & work, search & search);



#endif