#include "internetworm.h"
#include <string>
#include <fstream>
#include <iostream>

bool URL::Download (std::string &page){
//to be updated
    std::string order = "wget -q --tries=3 --timeout=2 \"" + _url + "\""+ " -O index.html";
    system(order.c_str());
    std::ifstream fin;
    fin.open("index.html");
    if(!fin.is_open()){
        system("rm -rf index.html");
        return 0;
    }
    while (!fin.eof()){
        std::string tmp;
        getline(fin, tmp);
        page += tmp;
    }system("rm -rf index.html");
    return 1;
}