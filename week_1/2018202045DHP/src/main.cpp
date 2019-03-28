#include "internetworm.h"
#include <string>
#include <set>
#include <queue>
#include <fstream>
#include <iostream>
//using namespace std;


const static std::string EMPTY = " ";
const static std::string ROOT_URL = "http://info.ruc.edu.cn/index.php";


int main(){
    std::queue <std::string> urls;
    std::set <std::string> visited;

    urls.push(ROOT_URL);
    visited.insert(ROOT_URL);
    visited.insert(EMPTY);
    std::ofstream fout;
    fout.open("results.out");
    while(!urls.empty()){
//        std::cerr << 1 << std::endl;
        std::string page;
        std::string currenturl = urls.front();
        urls.pop();
        
        bool opencorrectly = Loader(currenturl, page);
//        std::cerr << page << std::endl;
        if(!opencorrectly) continue;
        fout << "\n/*****   " << currenturl << "   *****/" << std::endl;
        fout << page << std::endl;
        std::queue <std::string> rawurls;
        Extracter(page, rawurls);

        while(!rawurls.empty()) {
            std::string newurl = rawurls.front();
            rawurls.pop();
            std::string tmp = Filter(currenturl, newurl);
            if(visited.count(tmp) == 0) {
                urls.push(tmp);
                visited.insert(tmp);
            }
        }
        std::cerr << urls.size() << ' ' << visited.size() << ' ' << currenturl << std::endl;
    }return 0;
}
