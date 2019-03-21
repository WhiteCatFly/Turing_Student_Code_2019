#include"parse.h"
#include<iostream>
#include<regex>
#include<string>
#include<set>
#include<cstdlib>
#include<queue>
#include<algorithm>
#include<fstream>
using namespace std;
extern string sensitive_words[100];
extern string current_url;
extern queue<string>url_to_be_crawled;
extern set<string>url_already_be_crawled;
void parseUrls(string &src,set<string> &store){
    //regex pattern("<a href=\"(.*?)\"");
    regex pattern("<a href=\"((?!http://)(?!http/,/.://)(.*?))\"");
    smatch urls;
    while(regex_search(src,urls,pattern)){
        //store.insert(urls[1].str());
       // cout<<urls[1].str()<<endl;
       string temp=urls[1].str();
       int flag=0;
       for(int i=0;sensitive_words[i]!="words_end";i++){
           if(temp.find(sensitive_words[i])!=temp.npos){
               flag++;break;
           }
       }
       if(!flag)store.insert(temp);
        src=urls.suffix();
    }

}
