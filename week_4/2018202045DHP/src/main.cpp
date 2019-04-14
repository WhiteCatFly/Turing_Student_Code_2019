#include "htmlparser.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>

const std::regex DOCTYPE("DOCTYPE|doctype");

void Error(){
    std::cerr << "Download failed" << std::endl;
    std::cerr << "Your file which stands order should be named as \"rooturl.txt\"" << std::endl;
}

void outDOCTYPE(){
    std::cerr << "I FIND DOCTYPE YEEAAAAHHHHHHHH." << std::endl;
}

void CleanLine(std::string &x){
    while(x[0] != '\n') x.erase(0, 1);
    x.erase(0, 1);
}

int main(){
//   iniloader();
    std::ofstream tree("tree.out");
    std::ofstream title("title.out");
    std::ofstream content("content.out");
    std::ofstream link("link.out");
    std::string page_string;
    if(!Download(page_string)){
        Error();
        return 0;
    }
    std::istringstream page(page_string);
    while(1){
        std::string tmp;
        getline(page, tmp);
        CleanLine(page_string);
        if(regex_search(tmp, DOCTYPE)){
//            outDOCTYPE();
            break;
        }
    }
//    std::cerr << page_string << std::endl;
    MainBodyAnalyzer(tree, title, content, link, page_string);
}