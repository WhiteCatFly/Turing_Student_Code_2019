#include "internetworm.h"
#include <string>
#include <fstream>
#include <iostream>

URL::URL (std::string url){
    _url = url;
}

void URL::Show(std::ostream &out) {
    out << "|*****     " << _url << "     *****|" << std::endl;
}

std::string URL::Visit() const {
    return _url;
}

bool operator < (const URL x, const URL y){
    return x.Visit() < y.Visit();
}

bool operator > (const URL x, const URL y){
    return x.Visit() > y.Visit();
}

std::string URL::View(){
    return _url;
}