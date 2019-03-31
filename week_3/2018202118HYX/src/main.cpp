#include"head.h"

int main()
{
    string root="http://econ.ruc.edu.cn/";
    int total=0;
    
    queue<string> todo;
    set<string> done;
    set<string>urls;
    
    string current_url;
    todo.push(root);

    while(!todo.empty() )
    {
        current_url=todo.front();
        todo.pop();
        done.insert(current_url);

        parse_url s(current_url,root);
        s.get_content(total);
        urls.clear();
        s.parse(urls);

        for(auto url:urls)
        {
            if(done.find(url)==done.end())
                todo.push(url);
        }
    }
    cerr<<"total:"<<total<<endl;
    return 0;
}