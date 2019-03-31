#include"getcontent.h"
#include<iostream>
#include<regex>
#include<string>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<queue>

using namespace std;
extern string current_url;
extern queue<string>url_to_be_crawled;
extern set<string>url_already_be_crawled;

string getContent(string &url,int times){
    string to_be_stored = to_string(times);

    to_be_stored += ".html";
    if(url!="info.ruc.edu.cn"){
        url = "info.ruc.edu.cn/"+url;
        //cout<<url<<endl;
    }
    string final = "wget -O "+to_be_stored+' '+url;
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