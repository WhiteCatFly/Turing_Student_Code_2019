#ifndef _SEARCH_H
#define _SEARCH_H

#include <string>
#include <vector>

const std::string BLACK_CHARACTER[] = 
{
    "，",
    "。",
    "/",
    ".",
    "、",
    "？",
    "?",
    ",",
    " ",
    ":",
    ">",
    "<",
    "：",
    "）",
    "（",
    "】",
    "【",
    "[",
    "]",
    " ",
    "﻿",
    ";",
    "(",
    ")",
    "-",
    "//",
    "__",
    "=",
    "+",
    "；",
};

bool isEmptyChar(std::string str);

std::vector<std::string> search(std::string &queryStr);
#endif