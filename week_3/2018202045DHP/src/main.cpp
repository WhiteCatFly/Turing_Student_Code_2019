#include "internetworm.h"
#include <string>
#include <set>
#include <queue>
#include <regex>
#include <fstream>
#include <iostream>
//using namespace std;

//std::regex Debug("//./");
//std::smatch result;

const static URL EMPTY((std::string)(" "));
//to be updated
//const static std::string ROOT_URL = "http://info.ruc.edu.cn/";
URL ROOT_URL;
std::string BANNED;

int main(){
    std::queue <URL> urls;
    std::set <URL> visited;
    LogLoader();
    
    urls.push(ROOT_URL);
    visited.insert(ROOT_URL);
    visited.insert(EMPTY);

    std::ofstream fout;
    fout.open("results.out");
    while(!urls.empty()){
        std::string page;
        URL currenturl(urls.front());
        urls.pop();
        if(!currenturl.Download(page))
            continue;
        currenturl.Show(fout);
        fout << page << std::endl;
        std::queue <URL> rawurls;
        Extracter(page, rawurls);

        while(!rawurls.empty()) {
            URL newurl = rawurls.front();
            rawurls.pop();
            URL tmp = Filter(currenturl.Visit(), newurl.Visit());
/*            if(std::regex_search(tmp, result, Debug)){
                std::cerr << currenturl << ' ' << newurl << std::endl;
            }*/
            if(visited.count(tmp) == 0) {
                urls.push(tmp);
                visited.insert(tmp);
            }
        }
        std::cerr << urls.size() << ' ' << visited.size() << ' ' << std::endl;
        currenturl.Show(std::cerr);
    }return 0;
}
