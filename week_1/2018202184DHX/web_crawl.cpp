#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/wait.h>
#include<unistd.h>
#include<set>
#include<queue>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include<regex>
using namespace std;


std::string page_content;
void UrlToFile(string current_url,int count)                    //wget page file
{
    cout << "Now the Put In is :" << ("wget \"" + current_url + "\" -O " + std::to_string(count) + ".html").c_str() << endl;
    system(("wget \"" + current_url + "\" -O " + std::to_string(count) + ".html").c_str());
    return;
}

void FileToString(int count)                                    //store the content in url
{
    page_content.clear();
    char temp[100];
    sprintf(temp,"%d.html",count);
    FILE *fp = fopen(temp,"r");
    char c = fgetc(fp);
    while(c != EOF){
        page_content.push_back(c);
        c = fgetc(fp);
    }
    fclose(fp);
    return ;
}


int main()
{
    std::queue <string> url_to_be_crawled;
    std::set <string> url_already_crawled;
    std::string current_url = "info.ruc.edu.cn";

    char BlackList[20][20] = {".doc" , ".pdf" , ".xls" , "@" , ".css" , "/en/"};
    int count = 0;
    int flag;

    std::regex regex ("%*(href=\")([^\"]*)");
    std::smatch res;

    url_already_crawled.insert(current_url);
    url_already_crawled.insert("info.ruc.edu.cn/index.php");
    url_to_be_crawled.push(current_url);
    while(!url_to_be_crawled.empty())
    {
        count ++;
        current_url.clear();
        current_url = url_to_be_crawled.front();
        cout << "Now Current URL is:" << current_url <<endl;
        UrlToFile(current_url,count);
        FileToString(count);
        cout << "OK Begin" << endl;
        //printf("%s\n",page_content);
        while(regex_search(page_content,res,regex))
        {
            for(int x = 0; x < 6; x++)
            {
                if(res[2].str().find(BlackList[x],0) != res[2].str().npos)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag)
            {
                flag = 0;
            }
            else if(res[2].str().find("http:\/\/",0) != res[2].str().npos)          
            {
                str = res[2].str();
                str.erase(str.begin(),str.begin() + 7);
                if(str.find("info.ruc.edu.cn",0) != str.npos)
                {
                    if(url_already_crawled.find(str) == url_already_crawled.end())
                    {
                        url_to_be_crawled.push(str);
                        url_already_crawled.insert(str);
                    }
                }
            }
            else
            {
                std::string tempo;
                tempo.clear();
                if(res[2].str().find(".php",0) != res[2].str().npos)
                {
                    if(*res[2].str().begin() == '/')    
                    {
                        tempo = "info.ruc.edu.cn" + res[2].str();
                    }
                    else
                    {
                        tempo = "info.ruc.edu.cn/" + res[2].str();
                    }
                    if(url_already_crawled.find(tempo) == url_already_crawled.end())
                    {
                        url_to_be_crawled.push(tempo);
                        url_already_crawled.insert(tempo);
                    }
                }
                else if(res[2].str().find(".html",0) != res[2].str().npos)
                {
                    if(*res[2].str().begin() == '/')    
                    {
                        tempo = "info.ruc.edu.cn" + res[2].str();
                    }
                    else
                    {
                        tempo = "info.ruc.edu.cn/" + res[2].str();
                    }
                    if(url_already_crawled.find(tempo) == url_already_crawled.end())
                    {
                        url_to_be_crawled.push(tempo);
                        url_already_crawled.insert(tempo);
                    }
                }
                else if(res[2].str().find('.',0) == res[2].str().npos)
                {
                    if(*res[2].str().begin() == '/')    
                    {
                        tempo = "info.ruc.edu.cn" + res[2].str();
                    }
                    else
                    {
                        tempo = "info.ruc.edu.cn/" + res[2].str();
                    }
                    if(url_already_crawled.find(tempo) == url_already_crawled.end())
                    {
                        url_to_be_crawled.push(tempo);
                        url_already_crawled.insert(tempo);
                    }
                }
            }
            page_content = res.suffix();
        }
        url_to_be_crawled.pop();
    }
    printf("%d",count);
    return 0;
}