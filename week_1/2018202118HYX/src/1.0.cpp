#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<regex>
#include<set>
using namespace std;

string root="http://info.ruc.edu.cn";
int total=0;

queue<string> todo;//队列+BFS
set<string> done;//存储所有URL
set<string>urls;

ifstream fin;

string get_content(string current_url)
{
    total++;

    string content;
    string order="wget http://info.ruc.edu.cn/";
    string open_way=" -O /home/hyx/index.html";
    string file="/home/hyx/index.html";
    string line;

    if(current_url!=root)
        order=order+current_url+open_way;
    system(order.c_str());

    fin.open(file);
    while (getline(fin,line))
        content+=line;
    //cerr<<"123"<<endl;
    return content;
}

void parse(string content,string current_url)
{
    regex pattern("<a href=\"((?!http://)(?!http/,/.://)(.*?))\"");
    smatch s;
    while(regex_search(content,s,pattern))
    {
        urls.insert(s[1].str());
        content=s.suffix();
    }
}

int main()
{
    string current_url;
    todo.push(root);

    while(!todo.empty() )
    {
        current_url=todo.front();//从队列中获取当前网址
        todo.pop();//从队列中删除当前网址
        done.insert(current_url);//向set容器中插入当前网址

        string content=get_content(current_url);//读取当前网页
        urls.clear();//清空当前网页url容器
        parse(content,current_url);//解析当前网页获得所有URL并存入set中

        for(auto url:urls)//遍历当前网址set容器中的URL
        {
            if(done.find(url)==done.end())//若未访问过
                todo.push(url);//存入队列中以待访问
        }
    }
    cerr<<"total:"<<total<<endl;
    return 0;
}