#include"something.h"

string get_content(string current_url,int &total)
{
    total++;

    string content;
    string order="wget ";
    string open_way=" -O /home/hyx/index.html";
    string file="/home/hyx/index.html";
    string line;

    order=order+current_url+open_way;
    system(order.c_str());

    ifstream fin;
    fin.open(file);
    while (getline(fin,line))
        content+=line;
    //cerr<<"123"<<endl;
    return content;
}

int match(string url)
{
    string m1="http://";
    string m2="info.ruc.edu.cn";
    if(url.find(m1)!=string::npos)//含http
    {
        if(url.find(m2)==string::npos)//不含info.ruc.edu.cn
            return 0;
        else//http://info.ruc.edu.cn/
            return 1;    
    }
    else//不含http
    {
        string m[]={"@ruc.edu.cn",".css",".pdf",".doc",".xls",".ppt"};
        for(int i=0;i<6;i++)
        {
            if(url.find(m[i])!=string::npos)
                return 0;
        }
        return 2;
    }
    
}

int ifadjust(string url)
{
    for(int i=url.length()-1;i>=0;i--)
    {
        if(url[i]=='/')
        {
            if(url[i-1]=='/')
                return 0;
            else
                return (url.length()-i-1);//有单斜杠需要替换当前目录
        }
    }
    return 0;
}

string adjust(string url,string current_url)
{
    int p=ifadjust(current_url);
    if(p==0)
    {
        return (current_url+'/'+url);
    }
    else
    {
        current_url.erase(current_url.length()-p,p);
        return (current_url+url);
    }
    
}

void parse(string content,string current_url,set<string>&urls)
{
    //cout<<current_url<<endl;
    regex pattern("<a href=\"([^ <>\\n]+)\"");
    smatch s;
    while(regex_search(content,s,pattern))
    {
        content=s.suffix();
        
        string a_url=s[1].str();
        int x=match(a_url);
        if(x==0)
            continue;
        if(x==1)
        {
            if(a_url[a_url.length()-1]=='/')
                 a_url.erase(a_url.length()-1,1);
            urls.insert(a_url);
            continue;
        }
        if(x==2)
        {
            a_url=adjust(a_url,current_url);
            urls.insert(a_url);
            continue;
        }
        //cout<<x<<" "<<a_url<<endl;
    }
}