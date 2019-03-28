#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<queue>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<regex>
using namespace std;
const string sensitive_words[100]={
    ".css",".doc",".docx",".xls",".xlsx",".txt",".jpg",".png","bmp",
    ".jpeg",".flv",".mp4",".avi","@ruc.edu.cn",".pdf","str = str+","words_end"
};
string current_url = "info.ruc.edu.cn";

queue<string>url_to_be_crawled;

set<string>url_already_be_crawled;

string getContent(string &url,int times){
    string to_be_stored = to_string(times);

    to_be_stored += ".html";
    if(url!="info.ruc.edu.cn"){
        url = "info.ruc.edu.cn/"+url;
        cout<<url<<endl;
    }
    string final = "wget -q -O "+to_be_stored+' '+url;
    //wget website's src code 
    //store them ,naming by turns 

    const char *key=final.c_str();                                                                                       
    system(key);

    ifstream fin ;
    fin.open(to_be_stored);
    string temp,ans;
    while(getline(fin,temp)){
        ans+=temp;
    }
    fin.close();
    return ans;
}
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
int main(){
    url_to_be_crawled.push(current_url);
    int n = 0;

    while(!url_to_be_crawled.empty()){
    n++;
    
    current_url = url_to_be_crawled.front();
    //cerr << url_to_be_crawled.size() << ' ' << current_url << endl;
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
