#include "bfs.h"
std::queue <std::string> url_to_be_crawled;
std::set <std::string> url_already_crawled;
std::string current_url;
std::string page_content;
int count = 0;
void bfs()
{
    const std::string root = "info.ruc.edu.cn";
    const int MAX = 20;
    const char BlackList[][MAX] = {".doc" , ".pdf" , ".xls" , "@" , ".css"};

    std::regex regex ("%*(href=\")([^\"]*)");
    std::smatch res;

    url_already_crawled.insert(root);
    url_already_crawled.insert(root + "/index.php");
    url_to_be_crawled.push(root + "/index.php");
    while(!url_to_be_crawled.empty())
    {
        count ++;
        current_url.clear();
        current_url = url_to_be_crawled.front();
        UrlToFile(current_url,count);
        FileToString(count);
        while(regex_search(page_content,res,regex))
        {
            std::string url = res[2].str();
            if(BlackListCheck(url))
            {
                if(JudgeReOrAb(url))
                {
                    AbsoluteSite(url);
                }
                else
                {
                    RelativeSite(url);
                }
            }
            page_content = res.suffix();
        }
        url_to_be_crawled.pop();
    }
    printf("%d",count);
    return;
};