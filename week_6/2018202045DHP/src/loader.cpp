#include "internetworm.h"
#include <set>
#include <queue>
#include <regex>
#include <fstream>
#include <iostream>

extern URL ROOT_URL;
extern std::regex BANNED;
extern std::string DOWNLOAD;

void DelEnter(std::string &x){
    while(x[x.length() - 1] == '\r' || x[x.length() - 1] == '\n')
        x.pop_back();
}

int NumberAnalyzer(std::string x){
    int tmp = 0;
    for(int i = 0; i < x.size(); i++){
        if(x[i] < '0' || x[i] > '9') break;
        tmp = tmp * 10 + x[i] - '0';
    }return tmp;
}

void IniLoader(){
    std::ifstream ini;
    ini.open("personalsettings.ini");
    if(!ini.is_open()){
        std::cerr << "Cannot open your personal settings correctly." << std::endl;
        std::cerr << "Please check that file which should be named as \"personalsettings.ini\"." << std::endl;
        std::cerr << "To learn more, please refer to the \"README.txt\"." << std::endl;
        ROOT_URL = EMPTY;
        return;
    } else {
        std::string ROOT_URL_TMP;
        getline(ini, ROOT_URL_TMP);
        DelEnter(ROOT_URL_TMP);
        ROOT_URL = ROOT_URL_TMP;

        std::string BANNED_TMP;
        getline(ini, BANNED_TMP);
        DelEnter(BANNED_TMP);
        BANNED = BANNED_TMP;

        std::string DOWNLOAD_TMP;
        getline(ini, DOWNLOAD_TMP);
        DelEnter(DOWNLOAD_TMP);
        DOWNLOAD = DOWNLOAD_TMP;
    }
}

bool BreakpointLoader(std::queue<URL> &waitinglist, std::set<URL> &repeatjudge){
    std::ifstream ini;
    ini.open("backup.ini");
    if(!ini.is_open()){
        std::cerr << "Cannot open breakpoint saving file correctly." << std::endl;
        std::cerr << "Please check that file which should be named as \"backup.ini\"." << std::endl; 
        std::cerr << "To learn more, please refer to the \"README.txt\"." << std::endl;
        return 0;
    } else {
        int tmpnum;
        std::string tmpstr; 
        getline(ini, tmpstr);
        DelEnter(tmpstr);
        tmpnum = NumberAnalyzer(tmpstr);
        for(int i = 1; i <= tmpnum; i++){
            getline(ini, tmpstr);
            DelEnter(tmpstr);
            waitinglist.push(tmpstr);
        }

        getline(ini, tmpstr);
        tmpnum = NumberAnalyzer(tmpstr);
        for(int i = 1; i <= tmpnum; i++){
            getline(ini, tmpstr);
            DelEnter(tmpstr);
            repeatjudge.insert(tmpstr);
        }
    }return 1;
}