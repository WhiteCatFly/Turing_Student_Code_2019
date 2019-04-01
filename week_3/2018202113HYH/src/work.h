#ifndef WORK_H
#define WORK_H

#include <set>
#include <iostream>
#include <string>
#include <regex>


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

     
     void judge(std::string str_,int mark);
     void judge_slash();
     void judge_mark();

     void parse()           //正则表达式匹配
    {
        std::regex  pattern("href=[\'\"]?([a-z0-9_:\\/.\\?=&]+)[\'\"]?");
        std::regex  jump("window.location.href=\"([a-z0-9_:\\/.]+)\"");
    

        std::smatch res;
        std::string _content = content;
   
        while(regex_search(_content,res,pattern))
       {   
       
         //cout<< a[0].str() <<endl;
         judge(res[1].str(),0);
         //cout<< a[1].str() <<endl;
        
         _content = res.suffix();
        
        }
        while(regex_search(content,res,jump))
        {
        
         judge(res[1].str(),1);
         content = res.suffix();

        }

    }
     
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


#endif

