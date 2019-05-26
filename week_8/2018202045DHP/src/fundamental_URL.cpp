#include "internetworm.h"
#include <iostream>
#include <fstream>
#include <sstream>
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

std::string URL::OriginChinese(){
    return _Chinese;
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

void URL::WriteChinese(std::ostream &out){
    for(int i = 0; i < _page.size(); i++){
        std::string temp;
        if(_page[i] < 0 && i + 2 < _page.size())
            while(1){
                if(_page[i] < 0 && _page[i + 1] < 0 && _page[i + 2] < 0){
                    temp.push_back(_page[i]);
                    temp.push_back(_page[i + 1]);
                    temp.push_back(_page[i + 2]);
                    i += 3;
                }else if(temp.size() != 0 && (isdigit(_page[i]) || _page[i] == ' ' )){
                    temp.push_back(_page[i]);
                    i++;
                }else break;
            }
        if(temp.size() > 0)
            out << temp << std::endl;
        //std::cerr << i << ' ' << _page.size() << std::endl;
    }
}

void URL::FilterChinese(){
    for(int i = 0; i < _page.size(); i++){
        std::string temp;
        if(_page[i] < 0 && i + 2 < _page.size())
            while(1){
                if(_page[i] < 0 && _page[i + 1] < 0 && _page[i + 2] < 0){
                    temp.push_back(_page[i]);
                    temp.push_back(_page[i + 1]);
                    temp.push_back(_page[i + 2]);
                    i += 3;
                }else if(temp.size() != 0 && (isdigit(_page[i]) || _page[i] == ' ' )){
                    temp.push_back(_page[i]);
                    i++;
                }else break;
            }
        if(temp.size())
            _Chinese += temp + "\n";
        //std::cerr << i << ' ' << _page.size() << std::endl;
    }
}