#include"HTMLparser.h"
#include<utility>
#include<set>

class Crawler{
private:
    std::vector<std::pair<std::string, HTMLparser>>pairs; //建立每一个url和它相关信息的关系
    std::set<std::string> whole_result;
    std::queue<std::string> to_be_crawled;
    std::string Current_url;
    int index;
public:
    Crawler(){};
    ~Crawler(){};
    Crawler(const HTMLparser& other);
    void Run();
    void Check(); //重爬函数
    void Output(const std::string&file_name);
};