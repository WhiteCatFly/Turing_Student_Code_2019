#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <map>
#include <set>

extern std::string root_url;

extern std::ofstream fout, ferr;

extern std::set<std::string> visit; // 排重
extern std::queue<std::string> waiting; // bfs 等待队列
extern std::vector<std::string> working; // 本次 multihandle 处理的 url
extern std::vector<std::string*> results; // 本次 multihandle 结果 html 存放
extern std::map<std::string, int> fail_time; // 因网络问题重连次数

extern int page_cnt, //处理网页总数
           page_num; // 当前 multihandle 处理成功页面数

void push_into_waiting(std::string &x);

void save_to_file(std::string url, std::string* res);

void bfs();

#endif