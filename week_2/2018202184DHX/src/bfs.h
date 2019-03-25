#ifndef BFS_H_INCLUDED
#define BFS_H_INCLUDED

#include "UrlToString.h"
#include "StringOperate.h"
#include <regex>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <set>
#include <queue>

extern std::queue <std::string> url_to_be_crawled;
extern std::set <std::string> url_already_crawled;
extern std::string current_url;
extern std::string page_content;
extern int count;
void bfs();

#endif