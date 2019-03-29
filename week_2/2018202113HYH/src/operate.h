#ifndef OPERATE_H
#define OPERATE_H

#include <algorithm>
#include <vector>
#include <regex>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <ctime>

const std::string root = "info.ruc.edu.cn";

//using namespace std;

void judge ( std::string str , std::string &current , std::set<std::string> &urls_tobe_judged );

std::string getcontent ( std::string &current , int &total_urls , std::string &storage_path );

void parse ( std::string &content , std::string &current , std::set<std::string> &urls_tobe_judged );

#endif