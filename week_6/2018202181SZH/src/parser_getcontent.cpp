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


string WEB::getContent(int times){
    string to_be_stored = to_string(times);

    to_be_stored += ".html";

        if(current_url.find(root_url) == current_url.npos ){
            if(times != 1){
                if(current_url[0] == '/') current_url = root_url  + current_url;
                    else current_url = root_url + '/' + current_url;
            }
        
        }   
        
    string final = "wget -O "+to_be_stored+"  "+'\"'+current_url+'\"'+" -a down.log";
    //string final = "wget -O "+to_be_stored+" --timeout=10 --waitretry=0 --tries=5  "+'\"'+current_url+'\"';
    //wget website's src code
    //store them ,naming by turns
        cout<<current_url<<endl;
    cout<<final<<endl;
    const char *key=final.c_str();
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