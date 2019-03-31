#include"unit.h"
#include<iostream>
#include<string>
#include<queue>
#include<set>
#include<algorithm>
#include<cstdlib>
#include<fstream>
using namespace std;

extern std::string root_url;

void website::Bfs(){
    
    current_url = root_url;
    url_to_be_crawled.push(current_url);
   
    while(!url_to_be_crawled.empty()){
        n++;
        cout<<url_to_be_crawled.size()<<endl;
        current_url = url_to_be_crawled.front();
        url_to_be_crawled.pop();
        url_already_be_crawled.insert(current_url);
    //wget website page, store by fstream
        string page_content = getContent(n);

        set<string>url_current_page;

        parseUrls(page_content,url_current_page);

         for(auto x:url_current_page){
            if(url_already_be_crawled.find(x)==url_already_be_crawled.end()){

            url_to_be_crawled.push(x);
            url_already_be_crawled.insert(x);
           }
        }
    }
    ofstream fout;
    
}
