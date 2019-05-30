#include"Crawler.h"
#include"BuildIndex.h"
#include<regex>
#include<iostream>

std::string CMDparser::timeout = "2";
std::string CMDparser::tries = "2";
std::string CMDparser::filename = "default";


std::string Eraseblanks(const std::string &str)
{
    std::regex pattern(" ");
    return regex_replace(str, pattern, "");
}

int GetContent::tries = 2;
int GetContent::timeout = 2;
std::string GetContent::filename = "default";

int main(){
    HTMLparser host("info.ruc.edu.cn");
    Crawler crawl(host);
    crawl.Run();
    std::string str;
    while(std::cin >> str){
        if(str == "exit") return 0;
        crawl.Answer(str);
    }
}