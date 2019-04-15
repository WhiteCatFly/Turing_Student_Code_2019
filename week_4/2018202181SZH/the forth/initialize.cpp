#ifndef HTMLparser
#define HTMLparser
#include"HTMLparser.h"
using namespace std;
html::html(){
    cout<<"Please type the address to get content :"<<endl;
    cin>>store_place;
    cout<<endl;
    if(cin) cout<<"input address successfully!"<<endl;
}
void judge_url_or_file(string &line,html & web){
    cout<<"if you have input a file name,please type word \"file\""<<endl;
    cout<<"if you have input a url,please type word \"url\""<<endl;
    string classification;
    cin>>classification;
    if(classification == "file" ){
        ifstream fin;
        fin.open(line);
        if(!fin.is_open()){
            cout<<"Error opening,please try again!"<<endl;
            exit(1);
        }
        string temp;
        while(!fin.eof()){
            getline(fin,temp);
            web.html_code = web.html_code + temp;
        }
        fin.close();
        cout<<"fin the html_code from a file successfully!!!"<<endl;
    }
    if(classification == "url"){
        string command ="wget -O origin_url.html ";
        command = command + line;
        system(command.c_str());
        string filename = "origin_url.html";
        ifstream fin;
        fin.open(filename);
        if(!fin.is_open()){
            cout<<"Error opening,please try again!"<<endl;
            exit(1);
        }
        string temp;
        while(!fin.eof()){
            getline(fin,temp);
            web.html_code = web.html_code + temp;
        }
        
        fin.close();
        cout<<"fin the html_code from a url successfully!!!"<<endl;
    }
}
#endif // !HTMLparser
