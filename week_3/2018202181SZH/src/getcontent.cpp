#include"unit.h"
#include<regex>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<queue>
#include<string>
using namespace std;
extern string root_url;

void input_first_url(string &url){
    cout<<"Please input the first url:"<<endl;
    cin>>url;
    if(!cin){
        cerr<<"Error!!! Please try again"<<endl;
    }
    return ;
}

string website::getContent(int times){
    string to_be_stored = to_string(times);

    to_be_stored += ".html";

    
        if(current_url.find(root_url) == current_url.npos ){
            if(times != 1){
                if(current_url[0] == '/') current_url = root_url  + current_url;
                    else current_url = root_url + '/' + current_url;
            }
        
        }   
    
    
    
        
    string final = "wget -O "+to_be_stored+"  "+'\"'+current_url+'\"';
    //string final = "wget -O "+to_be_stored+" --timeout=10 --waitretry=0 --tries=5  "+'\"'+current_url+'\"';
    //wget website's src code
    //store them ,naming by turns
        cout<<current_url<<endl;
    cout<<final<<endl;
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