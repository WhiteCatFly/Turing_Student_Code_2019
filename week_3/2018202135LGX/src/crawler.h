#ifndef CRAWLER_H
#define CRAWLER_H

#define DEFAULT_FILENAME "result"

#include<iostream>
#include<set>
#include<queue>
#include<string>
#include<regex>
#include<algorithm>
#include<fstream>

class Crawler{

private:

    std::set<std::string> final_results;  //储存最终结果的set

    std::queue<std::string> temp_results;  //将要爬取网页的队列

    std::string web_content;  //网页源代码

    std::string current_url;  //将要爬取的网页

    const std::string temp_filename = "temp";  //wget临时生成的文件

    std::ofstream fout;

    int index;

    const std::string host;  //主页

public:

    Crawler(const std::string root, const std::string filename = DEFAULT_FILENAME):host(root), current_url(root),index(0){  //构造函数

        final_results.insert(root);

        temp_results.push(root);

        //current_url = root;

        //index = 1;

        std::string syscmd = "touch " +filename;

        system(syscmd.c_str());

        fout.open(filename);
    };


    void ParseURLs(); //将web_content下的url放入队列

    void GetContent(); //从current_url中读取网页内容，放入web_content里

    void bfs();  //广度优先搜索

    std::string trans_URLs(std::string aurl);  //爬取路径处理函数

    ~Crawler() { std::cout << index << " urls crawled." << std::endl; };  //析构函数
};

#endif