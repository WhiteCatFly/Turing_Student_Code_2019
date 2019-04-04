#include "internetworm.h"
#include <regex>
#include <string>
#include <iostream>

const static std::string EMPTY = " ";
//to be updated
//extern std::regex BANNED("(.css )|(@ruc.edu.cn )|(.png )|(.pdf )|(.PDF )|(.docx )|(.ico )|(.doc )|(.xls )|(.mp4 )|(.jpg )|(.xlsx )|(.ppt )|(.zip )|(.rar )");
//const static std::regex MUST("(http://info.ruc.edu.cn/)");
extern std::string BANNED;
extern URL ROOT_URL;
const static std::regex HOST("(http://)|(https://)");

inline void DelToSlash(std::string &x){
    while(x[x.length() - 1] != '/')
        x.pop_back();
}

inline void DelSlash(std::string &x){
    if(x[x.length() - 1] == '/')
        x.pop_back();
}

inline bool DDSChecker(std::string &x){
    if(x[0] == '.' && x[1] == '.' && x[2] == '/')
        return 1;
    return 0;
}

inline bool DSChecker(std::string &x){
    if(x[0] == '.' && x[1] == '/')
        return 1;
    return 0;
}

inline bool SChecker(std::string &x){
    if(x[0] == '/')
        return 1;
    return 0;
}

URL Filter  (std::string currenturl, std::string newurl){
//    std::cerr << currenturl << ' ' << newurl << ' ' << std::endl;
    static std::regex _BANNED(BANNED);
    static std::regex _MUST(ROOT_URL.Visit());  
    DelToSlash(currenturl);
    DelSlash(newurl);
    std::string judger = newurl + ' ';
    std::smatch result;
    if(std::regex_search(judger, result, _BANNED)){
        return EMPTY;
    }
    else if(std::regex_search(judger, result, HOST))
        if(std::regex_search(judger, result, _MUST))
            return newurl;
        else 
            return EMPTY;

    while(1)
        if(DDSChecker(newurl)){
            newurl.erase(0,3);
            DelSlash(currenturl);
            DelToSlash(currenturl);
        } else if(DSChecker(newurl))
            newurl.erase(0,2);
        else if(SChecker(newurl))
            newurl.erase(0,1);
        else break;

//    std::cerr << currenturl + newurl << std::endl;
    return currenturl + newurl; 
}
