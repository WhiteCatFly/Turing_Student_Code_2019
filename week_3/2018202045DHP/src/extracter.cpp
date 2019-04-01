#include "internetworm.h"
#include <iostream>
#include <string>
#include <queue>
#include <regex>

const static std::regex MATCHER("href=(\"[^\"]+\"|'[^']+'|[^\\s>)]+)");
//const static std::regex DEBUGGER("href=[^ >]+[ >]");

void Extracter (std::string &page, std::queue <URL> &newurls){
    std::smatch result;
    while(regex_search(page, result, MATCHER)){
        std::string tmp = result[1].str();
//        std::cerr << result[0].str() << std::endl;
        if(tmp[0] == '\'' || tmp[0] == '\"'){
            tmp.pop_back();
            tmp.erase(0,1);
        }
        URL _tmp(tmp);
        newurls.push(_tmp);
        page = result.suffix();
    }
    /*while(regex_search(page, result, DEBUGGER)){
        std::cerr << result[0].str() << std::endl;
        page = result.suffix();
    }*/
}