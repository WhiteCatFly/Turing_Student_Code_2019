#include<iostream>
#include"parser.h"
#include<fstream>
#include<string>
#include<sstream>
#include<regex>
#include<queue>
#include<cstring>
#include<set>
#include"crawler.h"
using namespace std;
parser::parser(ifstream* url)
{
    //cout<<"parser 调用成功";
    file_url=url;
}
parser::parser(string& url)
{
    //cout<<"parser 调用成功";
    target_url=url;
    string wget_url;
    wget_url="wget \""+url+"\" -O index -q";
    system(wget_url.c_str());
    file_url->open("index");
}
void parser::parse_title()
{
    file_url->clear();
    file_url->seekg(0);
    string col;
    smatch res;
    while(getline(*file_url,col))
    {        
        while(regex_search(col,res,regex("(%*<title>)([^<]*)(%*</title>)")))
        {
            //cout<<res[2].str()<<endl;
            return;
        }               
    }
}
void parser::parse_text()
{
    file_url->clear();
    file_url->seekg(0);
    get_text_bool.insert(" ");
    get_text_bool.insert("");
    string col;
    smatch res;    
    while(getline(*file_url,col))
    {        
        while(regex_search(col,res,regex("(%*>)([^<^\n]*)(%*<)")))
        {
            ret=get_text_bool.insert(res[2].str());
            if(ret.second)
                get_text.push(res[2].str());
            col=res.suffix();
        }               
    }
    /*while(!get_text.empty())
    {
        cout<<get_text.front()<<endl;
        get_text.pop();
    }*/
}
void parser::parse_url()
{
    file_url->clear();
    file_url->seekg(0);
    string col;
    smatch res;    
    while(getline(*file_url,col))
    {        
        while(regex_search(col,res,regex("(%*href=[\'\"]?)([^>^\'^\"]*)%*([\'\"]?)")))
        {
            get_url.push(res[2].str());
            col=res.suffix();
        }               
    }
    /*while(!get_url.empty())
    {
        cout<<get_url.front()<<endl;
        get_url.pop();
    }*/
}
