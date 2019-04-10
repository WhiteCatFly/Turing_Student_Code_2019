#include "htmlparser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

//constructor: analysing a string within "<>"
//f**k those useless space

std::string Parameter(std::string tmp){
    int i = 0;
    while(tmp[i] != '=') i++;
    tmp.erase(i, tmp.length() - i);
    return tmp;
}

std::string Value(std::string tmp){
    int i = 0;
    while(tmp[i] != '=') i++;
    tmp.erase(0, i+1);
    return tmp;
}

Element::Element(std::string x){
    terminated = false;
    content_ = EMPTY;
    if(x[x.length() - 1] == SLASH){
        x.pop_back();
        terminated = true;
    }
    
    std::istringstream head(x);
    std::string tmp;
    head >> type_;

    bool inquote = false;
    while(1){
        tmp = EMPTY;
        head >> tmp;
        if(tmp == EMPTY) break;
//        std::cerr << tmp << head.eof() << std::endl;
        if(inquote){ 
            value.front() += SPACE + tmp;
        }else{
            parameter.push_back (Parameter (tmp));
            value.push_back     (Value (tmp));
        }
        for(int i = 0; i < tmp.length(); i++)
            if(tmp[i] == QUOTE) inquote ^= 1;
    }
}

void Element::Terminate(){
    terminated = 1;
}

bool Element::is_end(){
    return terminated;
}

void Element::AddContent(std::string content){
    content_ += content;
}

void OutFormat(std::ostream &dir, int depth, std::string text){
    for(int i = 0; i < text.length(); i++){
        if(i != 0 && text[i] == '\n' && text[i - 1] == '\n')
            continue;
        if(i == 0 || text[i - 1] == '\n'){
            for(int j = 1; j < depth; j++)
                dir << "|   ";
            if(depth >= 1) 
                dir << "|---" ;
        }dir << text[i];
    }if(text[text.length() - 1] != '\n')
        dir << std::endl;
}

void Element::ShowFeature(std::ostream &dir, int depth){
    OutFormat(dir, depth - 1, type_);
    for(int i = 0; i < parameter.size(); i++){
        OutFormat(dir, depth, parameter[i]+" : "+value[i]);
    }
}

void Element::ShowContent(std::ostream &dir, int depth){
    while(content_.length() > 0 && (content_[0] == SPACE || content_[0] == TAB || content_[0] == '\n' || content_[0] == '\r'))
        content_.erase(0, 1);
    if(content_.length() == 0)
        content_=EMPTY;
    if(content_ == EMPTY)
        ;//        OutFormat(dir, depth, "content: NOTHING");
    else {
        OutFormat(dir, depth, "content:");
        OutFormat(dir, depth, content_);
    }
}

void Element::OutTitle(std::ostream &dir){
    if(type_ == "title")
        dir << content_ << std::endl;
}

void Element::OutContent(std::ostream &dir){
    dir << content_ << std::endl;;
}

void Element::OutLink(std::ostream &dir){
    for(int i = 0; i < parameter.size(); i++){
        if(parameter[i] == "href")
            dir << value[i] << std::endl;;
    }
}