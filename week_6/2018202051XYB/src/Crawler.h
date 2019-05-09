#ifndef _CRAWLER_H
#define _CRAWLER_H

#include <vector>
#include <string>
#include <queue>
#include <map>
#include <list>

#define STATUS_OK 200
#define STATUS_UNVIS 0
#define STATUS_FAIL -1

class Crawler
{
private:
    int num;
    std::list<std::string> waiting;
    std::map<std::string, int> urlStatus; 

public:
    Crawler() = default;
    Crawler(std::string &root);
    Crawler(std::ifstream &fvisit_, std::ifstream &flog_, int &pageNum);

    bool empty() { return num == 0; }
    bool isVisit(const std::string &url);
    int queryFailTime(const std::string url);
    void setSuccess(const std::string &url);
    bool queryFail(const std::string &url);
    void setFail(const std::string &url);

    std::vector<std::string> getNextBatch();
    void addUrl(const std::string &url);
    void setResponse(std::string url, std::string &content);
    void parseHTML(std::string &f_url, std::string &content);
    
};

std::string normalizeUrl(std::string url, std::string &f_url);

const std::string blackSubList[] = {
    ".css", ".js", ".png", ".jpg", ".jpeg", ".ico", ".mp4", ".mp3", ".flv",
    ".xls", ".xlsx", ".doc", ".ppt", ".docx", ".pptx", ".rar", ".zip", ".7z", ".pdf",
    "mailto", ".JPG", "javascript", ".bmp", ".gif"
};

#endif