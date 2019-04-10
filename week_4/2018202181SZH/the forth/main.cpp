#ifndef HTMLparser
#define HTMLparser
#include"HTMLparser.h"

int main(){
    cout<<"Please input the website which can be a url or a file name"<<endl;
    string name;
    cin>>name;
    html website;
    judge_url_or_file(name,website);
    website.inter_face();
}
#endif // !HTMLparser