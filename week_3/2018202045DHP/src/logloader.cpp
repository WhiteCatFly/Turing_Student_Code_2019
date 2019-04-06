#include "internetworm.h"
#include <iostream>
#include <fstream>
#include <string>

const static URL EMPTY((std::string)(" "));
extern URL ROOT_URL;
extern std::string BANNED;

inline void DelEnter(std::string &x){
    while(x[x.length() - 1] == '\n' || x[x.length() - 1] == '\r')
        x.pop_back();
}
void LogLoader(){
    std::ifstream log;
    log.open("parsesettings.log");
    if(!log.is_open()){
        std::cerr << "Please check your log file." << std::endl;
        std::cerr << "It should be named as \"parsesettings.log\". "<< std::endl;
        ROOT_URL = EMPTY;
    }else{
        std::string ROOT_URL_tmp;
        getline(log, ROOT_URL_tmp);
        DelEnter(ROOT_URL_tmp);
        ROOT_URL = ROOT_URL_tmp;

        getline(log, BANNED);
        DelEnter(BANNED);
    }
}