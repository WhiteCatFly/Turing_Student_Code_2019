#include<iostream>
#include<string>
#include"search.h"
#include<sstream>
extern void search(std::string,int);
int main(int argc,char * argv[])
{
    if(argc==3)
    {
    std::stringstream ss;
    ss<<argv[2];
    int require_number;
    ss>>require_number;
    Searchengine test=Searchengine(argv[1],require_number);
    }
    else
    {
    std::string query="信息";
    Searchengine test=Searchengine(query,10);
    }
}