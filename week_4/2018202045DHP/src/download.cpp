#include <string>
#include <fstream>

bool Download(std::string &page){
    std::string url;
    std::ifstream rooturl("rooturl.txt");
    rooturl >> url;
    std::string order = "wget -q --tries=3 --timeout=2 \"" + url + "\""+ " -O index.html";
    system(order.c_str());
    std::ifstream fin("index.html");
    if(!fin.is_open())
        return false;
    while(!fin.eof()){
        std::string tmp;
        getline(fin, tmp);
        page += tmp + '\n';
    }
    system("rm -rf index.html");
    return true;
}