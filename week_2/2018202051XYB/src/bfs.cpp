#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <unistd.h>

#include "my_curl.h"
#include "my_string.h"
#include "bfs.h"

std::string root_url("http://info.ruc.edu.cn/");

std::ofstream fout, ferr; // 成功下载 url 列表

std::set<std::string> visit; // 排重
std::queue<std::string> waiting; // bfs 等待队列
std::vector<std::string> working; // 本次 multihandle 处理的 url
std::vector<std::string*> results; // 本次 multihandle 结果 html 存放
std::map<std::string, int> fail_time; // 因网络问题重连次数


inline void push_into_waiting(std::string &x)
{
    if(!visit.count(x))
    {
        waiting.push(x);
        visit.insert(x);
    }
}

void save_to_file(std::string url, std::string &res)
{
    if(res.empty())
        return;

    url = url.substr(root_url.length());
    if(url[url.size() - 1] == '/' || url.empty())
        url = url + "index.html";
    
    std::size_t found = url.find_last_of("/");
    std::string path = "download/" + url.substr(0, found + 1);
    std::string order = "mkdir -p " + path;


    if(access(path.c_str(), 0) == -1)
        system(order.c_str());
    std::ofstream fw;
    fw.open(("download/" + url).c_str());
    fw << res;
    fw.close();
}


void bfs()
{
    int page_cnt = 0; //处理网页总数

    push_into_waiting(root_url);
    while(!waiting.empty())
    {   
        int page_num = 0; // 当前 multihandle 处理成功页面数
        multi(page_num);
        int index = working.size();
        for(int i = 0; i < index; i++)
        {
            // save to file
            save_to_file(working[i], *results[i]);

            // parse html
            parse_html(results[i], working[i]);

            delete results[i];
        }
        working.clear();
        results.clear();
       
        page_cnt += page_num;
        printf("new: %6d   total: %6d\n", page_num, page_cnt);

    }  
    std::cout << "Total : " << page_cnt << std::endl;
}
