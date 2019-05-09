#include "crawler.h"
#include <string>

using namespace std;

extern string root_url;


string craw::getContent(int times){
    string to_be_stored = to_string(times);
    to_be_stored += ".html";
    if(current_url.find(root_url) == current_url.npos ){
        if(times != 1){
            if(current_url[0] == '/') current_url = root_url  + current_url;
            else current_url = root_url + '/' + current_url;
        }
    }   
    string processed = "wget -O " + to_be_stored + "  " + '\"' + current_url + '\"' + " -a down.log";
    cout << current_url << endl;
    cout << processed << endl;
    const char *key = processed.c_str();
    system(key);
    ofstream fout_already;
    fout_already.open("diary_already_crawled.txt",std::ios::app);
    if(!fout_already.is_open()){
        cout<<"Fail to open the store file! "<<endl;
        exit(1);
    }
    fout_already<<current_url<<endl;
    fout_already.close();
    ifstream fin ;
    fin.open(to_be_stored);
    string temp,ans;
    while(getline(fin,temp)){
        ans+=temp;
    }
    fin.close();
    return ans;
}