#include "internetworm.h"
#include "htmlparser.h"
#include <iostream>
#include <fstream>
#include <string>

HtmlParser::HtmlParser(){}

HtmlParser::HtmlParser(URL x):
    URL(x)
{}

HtmlParser::~HtmlParser(){}

std::queue<URL> HtmlParser::Origin(){
    return _link;
}

bool HtmlParser::emptylink(){
    return _link.empty();
}

URL HtmlParser::frontlink(){
    return _link.front();
}

void HtmlParser::poplink(){
    _link.pop();
}