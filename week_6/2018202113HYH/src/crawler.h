#ifndef CRAWLER_H
#define CRAWLER_H
#include "parser.h"

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <set>
#include <regex>
#include <ctime>

using std::string;


class crawler
{
    public:
    friend void run_bfs(crawler &crawler);
    friend void if_find(crawler &crawler);
    
    crawler()
    {
        total_urls = 0;
    }
    crawler(string root_)
    {   
        root = root_;
    
        fout_crawled.open(file_crawled,std::ios::app);
        fout_tobe.open(file_tobecrawled,std::ios::app);
        fout.open(log,std::ios::app);

        if(!fout_crawled || !fout_tobe)
            fout << "error! can not open the file" << std::endl;
        string url;
        char test;
        total_urls = 0;

        fin_crawled.open(file_crawled);
        fin_tobe.open(file_tobecrawled);
        test = fin_tobe.peek();

        if(fin_tobe.eof())
        {
            urls_tobe_clawed.push(root);
            fout << "---------------------------" << std::endl;
            fout << "no breakpoint" << std::endl;
            fout << "start from the beginning" << std::endl;      
            //total_urls = 0;
        }
        else
        {   
            fout << "---------------------------"  << std::endl;
            fout << "start from the breakpoint" << std::endl;
            while(std::getline(fin_crawled,url))
            {
                total_urls ++;
                urls_clawed.insert(url);
            }
            fout << "(tip : crawled " << total_urls << " urls already)" << std::endl;
           
            while(std::getline(fin_tobe,url))
            {
                if(urls_clawed.find(url) == urls_clawed.end())
                    urls_tobe_clawed.push(url);
            }
            fin_tobe.close();
            fin_crawled.close();
        }
        
   

    }
    void delete_record()
    {
        fout.open("log.txt",std::ios::app);
        fout << "---------------------------"  << std::endl;
        remove("record.txt");
        remove("record_.txt");

        fout << "end last mission" << std::endl;

        fout.close();
    }
    void set_current(string str)     //获取当前url
    {
        current = str;
    }
    void get_path(string path)       //改变默认的sterage_path
    {
        storage_path = path;
    }
    string get_content();      //从content读取urls
    int get_num() const         //获得url的总数
    {
        return total_urls;
    }

    
    void worker(string content);
    //void judge(string str);
    void judge_slash(string &str);
    //void judge_mark(string &str);
    //void judge_jump(string &str);

    ~crawler()
    {

    }
    private:
    parser my_parser;
    int total_urls;
    //string content;
    string current;
    string file_crawled = "record.txt";    //记录已经爬取的url
    string file_tobecrawled = "record_.txt";    //记录urls_tobe_crawled的内容,程序正常结束时删除
    string log = "log.txt";    //日志
    string root;
    string record_str;      //经正则表达式解析到的string
    string storage_path = "/home/halcyon/index.html";
    std::set   <string> urls_tobe_judged;
    std::queue <string> urls_tobe_clawed;
    std::set   <string> urls_clawed;
    std::ofstream fout_crawled;
    std::ofstream fout_tobe;
    std::ofstream fout;
    std::ifstream fin_crawled;
    std::ifstream fin_tobe;

};

#endif