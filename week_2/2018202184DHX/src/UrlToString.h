#ifndef URLTOSTRING_H_INCLUDED
#define URLTOSTRING_H_INCLUDED

#include"bfs.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
inline void UrlToFile(std::string current_url,int count)                    //wget page file
{
    system(("wget \"" + current_url + "\" -O " + std::to_string(count) + ".html").c_str());
    return;
};
void FileToString(int count);

#endif