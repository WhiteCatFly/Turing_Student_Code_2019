#include"cmdparser.h"
#include<iostream>
#include<sstream>
#include<vector>

CMDparser::CMDparser(const std::string &str){
    if(str.empty() || str.find_first_not_of(" ") == std::string::npos){
        valid = false;
        return;
    }
    std::vector<std::string> patchs;
    std::stringstream temp(str); //使用stringstream
    std::string str_1;
    int k = 0;
    int i1 = 0;
    int i2 = 0;
    bool if_ = false;
    valid = true;
    while(temp >> str_1){
        if(str_1 == "crawl"){
            if_ = true;
            continue;
        }
        if(str_1.find("--timeout") == 0){
            i1 ++;
            if(i1 >= 2){
                std::cout << "Too many arguments!\n";
                valid = false;
            }
            if(str_1.find("=") == std::string::npos){
                temp >> str_1;
                if(str_1.find("=") != 0){
                    std::cout << "Usage: --timeout=[number] -> set the time limit to download a html by seconds\n";
                    valid = false;
                }
                if(str_1 == "="){
                    temp >> str_1;
                    for(int i = 0; i < str_1.length(); i ++){
                        if(str_1[i] > '9' || str_1[i] < '0'){
                            std::cout << "Usage: --timeout=[number] -> set the time limit to download a html by seconds\n";
                            valid = false;
                        }
                    }
                    timeout = str_1;
                }
                if(str_1.find("=") == 0 && str_1 != "="){
                    str_1 = str_1.substr(1, str_1.length() - 1);
                    for (int i = 0; i < str_1.length(); i++)
                    {
                        if (str_1[i] > '9' || str_1[i] < '0')
                        {
                            std::cout << "Usage: --timeout=[number] -> set the time limit to download a html by seconds\n";
                            valid = false;
                        }
                    }
                    timeout = str_1;
                }
            }
            if(str_1.find("=") != std::string::npos){
                str_1 = str_1.substr(str_1.find("=") + 1, str_1.length() - 1);
                if(str_1.find(" ") == std::string::npos){
                    timeout = str_1;
                }
                else{
                    str_1 = str_1.substr(str_1.find_last_of("=") + 1, str_1.length() - 1);
                }
                for (int i = 0; i < str_1.length(); i++)
                {
                    if (str_1[i] > '9' || str_1[i] < '0')
                    {
                        std::cout << "Usage: --timeout=[number] -> set the time limit to download a html by seconds\n";
                        valid = false;
                    }
                }
                timeout = str_1;
            }
            continue;
        }
        if (str_1.find("--tries") == 0)
        {
            i2 ++;
            if(i2 >= 2){
                std::cout << "Too many arguments!\n";
                valid = false;
            }
            if (str_1.find("=") == std::string::npos)
            {
                temp >> str_1;
                if (str_1.find("=") != 0)
                {
                    std::cout << "Usage: --tries=[number] -> set the time limit to download a html by seconds\n";
                    valid = false;
                }
                if (str_1 == "=")
                {
                    temp >> str_1;
                    for (int i = 0; i < str_1.length(); i++)
                    {
                        if (str_1[i] > '9' || str_1[i] < '0')
                        {
                            std::cout << "Usage: --tries=[number] -> set the time limit to download a html by seconds\n";
                            valid = false;
                        }
                    }
                    tries = str_1;
                }
                if (str_1.find("=") == 0 && str_1 != "=")
                {
                    str_1 = str_1.substr(1, str_1.length() - 1);
                    for (int i = 0; i < str_1.length(); i++)
                    {
                        if (str_1[i] > '9' || str_1[i] < '0')
                        {
                            std::cout << "Usage: --tries=[number] -> set the time limit to download a html by seconds\n";
                            valid = false;
                        }
                    }
                    tries = str_1;
                }
            }
            if (str_1.find("=") != std::string::npos)
            {
                str_1 = str_1.substr(str_1.find("=") + 1, str_1.length() - 1);
                if (str_1.find(" ") == std::string::npos)
                {
                    tries = str_1;
                }
                else
                {
                    str_1 = str_1.substr(str_1.find_last_of("=") + 1, str_1.length() - 1);
                }
                for (int i = 0; i < str_1.length(); i++)
                {
                    if (str_1[i] > '9' || str_1[i] < '0')
                    {
                        std::cout << "Usage: --tries=[number] -> set the trying times when downloading fails\n";
                        valid = false;
                    }
                }
                tries = str_1;
            }
            continue;
        }
        if(str_1 == "-O"){
            temp >> str_1;
            filename = str_1;
            continue;
        }
        patchs.push_back(str_1);
    }
    if(!if_){
        std::cout << "Invalid command. Use --help to see the usage." << std::endl;
        valid = false;
    }
    if(patchs.empty() && if_){
        std::cout << "URL unknown\n";
        valid = false;
    }
    url = patchs.front();
}




void Helpmsg::show(){
    std::cout << "Basic usage:\n" 
              << "crawl + [url](necessary) + [options](optional)\n\n"
              << "Available options:\n"
              << "--timeout=[number] -> set the time limit to download a html by seconds\n"
              << "--tries=[number] -> set the trying times when downloading fails\n"
              << "-O + file -> save the crawled website to the file. If the name isn't given, the results will be saved to \"result\"\n" ;
}