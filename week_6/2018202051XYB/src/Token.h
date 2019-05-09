#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>
#include <iostream>

#define TYPE_TAG 0
#define TYPE_TEXT 1
#define TYPE_COMMENT 2

class Token
{
private:
    int type_;
    std::string content_;

public:
    Token(std::string content, int type)
    {
        type_ = type;
        content_ = content;
    }
    bool empty()
    {
        for(auto x : content_)
            if(!isspace(x))
                return false;
        return true;
    }
    std::string getStr()
    {
        return content_;
    }
    int type()
    {
        return type_;
    }
};    

#endif