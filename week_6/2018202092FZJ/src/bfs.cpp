#include "crawler.h"
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;

extern std::string root_url;

void crawler::restart(string to_be_txt,string already_txt){
    int count_size = 0;
    std::ifstream set_file;
    set_file.open(already_txt,std::ifstream::in);
    string ReadLine;
    while(getline(set_file,ReadLine)){
            already.insert(ReadLine);
            ReadLine.clear();
            count_size ++;

     }
    set_n(count_size + 1);
    set_file.close();
    std::ifstream queue_file;
    queue_file.open(to_be_txt,std::ifstream::in);
    while(getline(queue_file,ReadLine)){
        to_be.push(ReadLine);
        ReadLine.clear();
    }
    queue_file.close();
    for(count_size;count_size >= 0;count_size --){
        to_be.pop();
    }
    return;
}
void crawler::Bfs(){
    current_url = root_url;
    craw_website.getString(root_url);
    to_be.push(current_url);
    while(!to_be.empty()){
        n++;
        cout << to_be.size()<<endl;
        current_url = to_be.front();
        string temp = current_url;
        craw_website.getString(temp);
        to_be.pop();
        already.insert(current_url);
        string page_content = craw_website.getContent(n);
        set<string>url_current_page;
        parseUrls(page_content,url_current_page);
        ofstream fout_to_be;
        fout_to_be.open("diary_to_be.txt",std::ios::app);
        if(!fout_to_be.is_open()){
            cout << "Fail to open the store file! " << endl;
            exit(1);
        }
        for(auto x:url_current_page){
            if(already.find(x) == already.end()){
                to_be.push(x);
                fout_to_be<<x<<endl;
                already.insert(x);
            }
        }
        fout_to_be.close();
    }
} 