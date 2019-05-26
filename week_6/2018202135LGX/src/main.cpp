#include"Crawler.h"
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
    std::string str;
    while(getline(std::cin, str)){
        if(Eraseblanks(str)== "exit"){
            exit(0);
        }
        if (Eraseblanks(str) == "--help")
        {
            Helpmsg::show();
            continue;
        }
        CMDparser cmd(str);
        if(cmd.Valid()){
            HTMLparser host(cmd);
            Crawler test(host);
            test.Run();
            test.Check();
            if(str.find("-O") != std::string::npos){
                test.Output(CMDparser::Filename());
            }
        }
    }
}