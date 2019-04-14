#include "htmlparser.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <stack>

const static std::regex matcher("<([^>]+)>");
const static std::regex termflag("</[a-zA-Z]+>");
//const static std::regex notes("!--");

void FlushBlank(std::string &tmp){
    for(int i = 0; i < tmp.length(); i++){
        if(tmp[i] == '='){
            while(i >= 1 && tmp[i - 1] == SPACE){
                tmp.erase(i - 1 ,1);
                i--;
            }while(i < tmp.length() - 1 && tmp[i + 1] == SPACE){
                tmp.erase(i + 1 , 1);
            }
        }else if(tmp[i] == '\n')
            while(i < tmp.length() - 1 && tmp[i + 1] == SPACE || tmp[i + 1] == TAB)
                tmp.erase(i + 1 ,1);
    }
}

void MainBodyAnalyzer(std::ostream &tree, std::ostream &title, std::ostream &content, std::ostream &link, std::string &page){
    
//    std::cerr << page << std::endl;
    std::stack <Element> storage;
    std::smatch result;

    FlushBlank(page);

    while(regex_search(page, result, matcher)){
        if(!storage.empty()){
            std::string content;
            for(std::string::iterator it = page.begin(); it != result[0].first; it++)
                content += *it;
            storage.top().AddContent(content);
        }
        std::string tmp = result[1].str();
//        std::cerr << tmp << std::endl;
        if(tmp[0] == '/'){
//            std::cerr << "terminated sth" << std::endl;
            storage.top().Terminate();
        }else if (tmp[0] == '!' && tmp[1] == '-' && tmp[2] == '-'){
            ;
        }else{
            storage.push(Element(tmp));
            storage.top().ShowFeature(tree, storage.size());
        }if(storage.top().is_end()){
 //           std::cerr << "popped sth" << std::endl;
            storage.top().ShowContent(tree, storage.size());
            storage.top().OutTitle(title);
            storage.top().OutContent(content);
            storage.top().OutLink(link);
            storage.pop();
        }
        page = result.suffix();
    }
}