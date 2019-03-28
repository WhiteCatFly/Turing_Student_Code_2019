#include <regex>
#include <string>

const static std::string EMPTY = " ";
const static std::regex BANNED("(.css )|(@ruc.edu.cn )|(.png )|(.pdf )|(.PDF )|(.docx )|(.ico )|(.doc )|(.xls )");
const static std::regex MUST("(http://info.ruc.edu.cn)");
const static std::regex HOST("(http://)|(https://)");

std::string Filter  (std::string currenturl, std::string newurl){
     //   cerr << currenturl << ' ' << newurl << ' ' << endl;
    while(currenturl[currenturl.length() - 1] != '/')
        currenturl.pop_back();
    if(newurl[newurl.length() - 1] == '/')
        newurl.pop_back();
    std::string judger = newurl + ' ';
    std::smatch result;
    if(std::regex_search(judger, result, BANNED)){
        return EMPTY;
    }
    else if(std::regex_search(judger, result, HOST)){
        if(std::regex_search(judger, result, MUST)){
            return newurl;
        }else {
            return EMPTY;
        }
    }
    return currenturl + newurl; 
}
