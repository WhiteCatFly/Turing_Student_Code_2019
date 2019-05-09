#include <regex>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>
#include<sstream>
#include<string.h>
#include<string>
class StringUtils
{
public:
    static double str2Double(const std::string & s);
        //字符串转double，以下类似
    static std::string double2Str(double d);
    static int str2Int(const std::string & s);
    static std::string int2Str(int i);
};


class Htmlparser{
    private:
    std::string source;
    std::string content;
    public:
     Htmlparser(std::string name);
    Htmlparser()=default;
    void readin();
    void gettitle();
    void getpara();
    void getpic();
    void geturl();
    void interface();
    std::string show(){return source;}

};
class spiderbase{
    public:
    spiderbase()=default;
    spiderbase(std::string _root,std::string _path="now");
    virtual ~spiderbase()
    {
        std::cout<<"the spider is finished"<<std::endl;
        std::cout<<"the total webs are "<<cnt<<std::endl;
    }
    std::string root;
    std::string path;
    int cnt=0;
    std::string current;
    std::string content;
    std:: set<std::string> urls;
    std::set<std::string> clawed;
    std::queue<std::string> tobe;
    
    std::string get_content(const std::string & _current);
    void parse(std::string & content, std::string & current,std::set<std::string> & urls);
    virtual void bfs();
    int category_urls(const std::string & res,std::set<std::string> & urls,std::string & current,int mode);
    std::string process_url_type1(const std::string & res,const std::string & current);
     std::string process_url_type2(const std::string & res,const std::string & current);
     std::string process_url_type3(const std::string & res,const std::string & current);
    
};
class spider :public spiderbase
{
    private:
    Htmlparser webparser;
    void bfs();//could deal with breakpoint
    void judge();//if there is a breakpoint
    public:
    spider(std::string _root,std::string _path="now"):spiderbase(_root,_path){
        std::cout<<"the spider is finished"<<std::endl;
    std::cout<<"the total webs are "<<cnt<<std::endl;
    std::cout<<"look up the website.txt and choose the No. of website you want to parser"<<std::endl;
    std::cout<<"if you don't want to parser web, just enter 0"<<std::endl;
    int no;
    std::cin>>no;
    while(no)
    {
        webparser=Htmlparser(StringUtils::int2Str(no));
        std::cout<<"look up website.txt and choose the No. of website to parser"<<std::endl;
        std::cout<<"if you don't want to parser web, just enter 0"<<std::endl;
        std::cin>>no;
    }
    }
    inline ~spider(){
        system("rm log.txt");
    }
}
