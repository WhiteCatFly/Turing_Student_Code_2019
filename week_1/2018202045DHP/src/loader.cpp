#include <string>
#include <fstream>
#include <iostream>

bool Loader (std::string url, std::string &page){
    std::string order = "wget -q --tries=3 --timeout=2 \"" + url + "\""+ " -O index.html";
//    std::cerr << url << std::endl;
    system(order.c_str());
    std::ifstream fin;
    fin.open("index.html");
    if(!fin.is_open()){
        system("rm -rf index.html");
        return 0;
    }
    while (!fin.eof()){
        char tmp;
        fin.get(tmp);
        page += tmp;
    }system("rm -rf index.html");
    return 1;
}