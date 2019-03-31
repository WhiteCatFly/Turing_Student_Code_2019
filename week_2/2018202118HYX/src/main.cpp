#include"something.h"

int main()
{
    string root="http://info.ruc.edu.cn";
    int total=0;

    queue<string> todo;//队列+BFS
    set<string> done;//存储所有URL
    set<string>urls;
    
    string current_url;
    todo.push(root);

    while(!todo.empty() )
    {
        current_url=todo.front();//从队列中获取当前网址
        todo.pop();//从队列中删除当前网址
        done.insert(current_url);//向set容器中插入当前网址

        string content=get_content(current_url,total);//读取当前网页
        urls.clear();//清空当前网页url容器
        parse(content,current_url,urls);//解析当前网页获得所有URL并存入set中

        for(auto url:urls)//遍历当前网址set容器中的URL
        {
            if(done.find(url)==done.end())//若未访问过
                todo.push(url);//存入队列中以待访问
        }
    }
    cerr<<"total:"<<total<<endl;
    return 0;
}