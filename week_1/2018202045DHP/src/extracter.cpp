#include <string>
#include <queue>
#include <regex>

const static std::regex MATCHER("href=\"([^ <>\\n]+)\"");

void Extracter (std::string &page, std::queue <std::string> &newurls){
    std::smatch result;
    while(regex_search(page, result, MATCHER)){
        newurls.push(result[1].str());
        page = result.suffix();
    }
}