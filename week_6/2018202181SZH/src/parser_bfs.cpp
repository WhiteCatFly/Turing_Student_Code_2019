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
void website::restart(string to_be_txt,string already_txt){
    int count_size = 0;
    std::ifstream set_file;
    set_file.open(already_txt,std::ifstream::in);

    string ReadLine;
    while(getline(set_file,ReadLine)){
            url_already_be_crawled.insert(ReadLine);
            ReadLine.clear();
            count_size ++;
        
    }
    set_n(count_size + 1);
    set_file.close();

    std::ifstream queue_file;
    queue_file.open(to_be_txt,std::ifstream::in);
    while(getline(queue_file,ReadLine)){
        url_to_be_crawled.push(ReadLine);
        ReadLine.clear();
    }
    queue_file.close();
    for(count_size;count_size >= 0;count_size --){
        url_to_be_crawled.pop();
    }
    return;
}
void website::Bfs(){
    
    current_url = root_url;
    WEB_site.getString(root_url);
    url_to_be_crawled.push(current_url);
   
    while(!url_to_be_crawled.empty()){
        n++;
        cout<<url_to_be_crawled.size()<<endl;

        

        current_url = url_to_be_crawled.front();
        string temp = current_url;
        WEB_site.getString(temp);
        url_to_be_crawled.pop();
        url_already_be_crawled.insert(current_url);
    //wget website page, store by fstream
        string page_content = WEB_site.getContent(n);

        set<string>url_current_page;

        parseUrls(page_content,url_current_page);

        ofstream fout_to_be;
        fout_to_be.open("diary_to_be_crawled.txt",std::ios::app);
        if(!fout_to_be.is_open()){
            cout<<"Fail to open the store file! "<<endl;
            exit(1);
        }
        
        

         for(auto x:url_current_page){
            if(url_already_be_crawled.find(x)==url_already_be_crawled.end()){

            url_to_be_crawled.push(x);
            fout_to_be<<x<<endl;
            url_already_be_crawled.insert(x);
           }
        }
        fout_to_be.close();
    
    
    }
       
}