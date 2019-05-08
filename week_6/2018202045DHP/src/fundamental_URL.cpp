#include "internetworm.h"
#include <iostream>
#include <fstream>
#include <string>

extern std::string DOWNLOAD;

URL::URL (){}

URL::URL (const std::string url):
    _url(url)
{}

URL::~URL (){}

URL operator + (const URL &x, const URL &y){
    return x._url + y._url;
}

bool operator < (const URL &x, const URL &y){
    return x._url < y._url;
}

bool operator > (const URL &x, const URL &y){
    return x._url > y._url;
}

std::ostream & operator << (std::ostream &x, const URL &y){
    x << y._url;
}

std::string URL::OriginLink(){
    return _url;
}

std::string URL::OriginPage(){
    return _page;
}

bool URL::Download(){
    std::string order = DOWNLOAD + " \"" + _url + "\" -O index.html";

    system(order.c_str());
    std::ifstream fin;
    fin.open("index.html");
    if(!fin.is_open()){
        _page = EMPTY;
        _available = false;
        std::cerr << order << std::endl;
    }else{
        while(!fin.eof()){
            std::string tmp;
            getline(fin, tmp);
            _page += tmp;
        }
        _available = true;
    }
    system("rm -rf index.html");
    return _available;
}

void URL::Write(std::ostream &out){
    out << "|*****     " << _url << "     *****|" << std::endl;
}

void URL::WritePage(std::ostream &out){
    out << "|*****     " << _url << "     *****|" << std::endl;
    out << _page << std::endl;
}