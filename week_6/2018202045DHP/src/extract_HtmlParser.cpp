#include "internetworm.h"
#include "htmlparser.h"
#include <string>
#include <regex>
#include <queue>

const static std::regex MATCHER("href=[ ]*(\"[^\"]+\"|'[^']+'|[^\\s>)]+)");

inline void Modifier(std::string &x){
    while(x[0] == '\''              || x[0] == '\"')                x.erase(0,1);
    while(x[x.size() - 1] == '\''   || x[x.size() - 1] == '\"' )    x.pop_back();
}

void HtmlParser::Extract (){
    std::smatch result;
    std::string page = this -> OriginPage();
    while(regex_search(page, result, MATCHER)){
        std::string tmp = result[1].str();
        Modifier(tmp);
        _link.push(tmp);
        page = result.suffix();
    }
}