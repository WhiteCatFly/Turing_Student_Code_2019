#include"head.h"
using namespace std;

Get::Get()
{
    url="info.ruc.edu.cn";
}

Get::Get(string url_)
{
    url=url_;
}

Get::~Get() {   }

void Get::getcontent(string& content,int n)
{
    string file = to_string(n)+".html";
    
    string order = "wget -a log.txt -O "+file+" -c -t 10 -T 10 \""+url+'\"';
    cout<<order<<endl;
    
    system(order.c_str());

    ifstream fin ;
    fin.open(file);
    string line;
    while(getline(fin,line))
    {
        content+=line;
    }
    fin.close();
    //cout<<*content<<endl;
    return;
}