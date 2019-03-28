#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<queue>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<regex>
#include<string>
#include"getcontent.h"
#include"parse.h"
using namespace std;
string sensitive_words[100]={
    ".css",".doc",".docx",".xls",".xlsx",".txt",".jpg",".png","bmp",
    ".jpeg",".flv",".mp4",".avi","@ruc.edu.cn",".pdf","words_end"
};
string current_url = "info.ruc.edu.cn";

queue<string>url_to_be_crawled;

set<string>url_already_be_crawled;



int main(){
    url_to_be_crawled.push(current_url);
    int n = 0;


    while(!url_to_be_crawled.empty()){
    n++;
    cout<<url_to_be_crawled.size()<<endl;
    current_url = url_to_be_crawled.front();
    url_to_be_crawled.pop();
    url_already_be_crawled.insert(current_url);
    //wget website page, store by fstream
    string page_content = getContent(current_url,n);

    set<string>url_current_page;

    parseUrls(page_content,url_current_page);

    for(auto x:url_current_page){
        if(url_already_be_crawled.find(x)==url_already_be_crawled.end()){

            url_to_be_crawled.push(x);
            url_already_be_crawled.insert(x);
           }
        }
    }
    return 0;
}
