#ifndef _MY_CRAWLER_H
#define _MY_CRAWLER_H

#include <vector>
#include <string>
#include <queue>
#include <map>

#define STATUS_OK 200
#define STATUS_UNVIS 0
#define STATUS_FAIL -1

class my_crawler
{
private:
    int num;
    std::queue<std::string> waiting;
    std::map<std::string, int> url_status; 

public:
    void init(std::string &root);
    
    bool empty() { return num == 0; }
    bool is_visit(const std::string &url);
    int query_fail_time(const std::string &url);
    void set_success(const std::string &url);
    bool query_fail(const std::string &url);
    void set_fail(const std::string &url);


    std::vector<std::string> get_next_batch();
    void add_url(const std::string &url);
    void set_response(std::string url, std::string &content);
    void parse_html(std::string &f_url, std::string &content);
    
};

std::string normalize_url(std::string url, std::string &f_url);

const std::string black_sub_list[] = {
    ".css", ".js", ".png", ".jpg", ".jpeg", ".ico", ".mp4", ".mp3", ".flv",
    ".xls", ".xlsx", ".doc", ".ppt", ".docx", ".pptx", ".rar", ".zip", ".7z", ".pdf",
    "mailto", ".JPG", "javascript", ".bmp", ".gif"
};



#endif