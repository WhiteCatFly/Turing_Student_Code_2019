#include"head.h"

parse_url::parse_url(string &current_url_,string &root_)
{
    this->current_url=current_url_;
    this->content.clear();
    this->root=root_;
}

parse_url::~parse_url()
{   }

void parse_url::get_content(int &total)
{
    total++;
    cout<<total<<endl;
    cout<<this->current_url<<endl;

    string order="wget -c --tries=10 --timeout=5 --waitretry=3 ";
    string open_way=" -O /home/hyx/index.html";
    string file="/home/hyx/index.html";
    string line;

    order=order+this->current_url+open_way;
    system(order.c_str());

    ifstream fin;
    fin.open(file);
    while (getline(fin,line))
        this->content+=line;
    //cerr<<"123"<<endl;
}

int parse_url::match(string url) const
{
    const string m1="http://";
    const string m2="https://";
    string m3=this->root;
    m3.erase(0,7);
    if(url.find(m1)!=string::npos||url.find(m2)!=string::npos)//含http
    {
        if(url.find(m1+m3)==string::npos&&url.find(m2+m3)==string::npos)//不含root
            return 0;
        else//http://+root
            return 1;    
    }
    else//不含http
    {
        const string m[]={"@ruc.edu.cn",".css",".pdf",".doc",".js",".jpg",".mp3",".mp4",".png",".zip",".bmp",".ico",".avi", ".ppt",".xls",".xlsx",".docx",".pptx",".JPG","mailto:","javascript","#","pdf","xml","rar","file://"};
        for(auto it: m)
        {
            std::string :: size_type if_find_it = url.find(it);

            if(if_find_it != std::string::npos)
            return 0;
        }
        return 2;
    }
}

int parse_url::ifadjust( ) const
{
    string url=current_url;
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

string parse_url::adjust(string url)
{
    int p=ifadjust( );
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

void parse_url::parse(set<string> &urls)
{
    regex pattern("href=[\'\"]?([a-z0-9_:\\/.\\?=&]+)[\'\"]?");
    smatch s;
    int num=0;
    while(regex_search(this->content,s,pattern))
    {
        num++;
        this->content=s.suffix();
        string a_url=s[1].str();
        cout<<a_url<<endl;
        int x=this->match(a_url);
        if(x==0)
            //continue;
        if(x==1)
        {
            if(a_url[a_url.length()-1]=='/')
                a_url.erase(a_url.length()-1,1);
            //urls.insert(a_url);
            //continue;
        }
        if(x==2)
        {
            if(a_url[0]=='/')
                a_url.erase(0,1);
            a_url=adjust(a_url);
            if(a_url[a_url.length()-1]=='/')
                a_url.erase(a_url.length()-1,1);
            //urls.insert(a_url);
            //continue;
        }
        cout<<num<<" "<<x<<" "<<a_url<<endl;
    }
}