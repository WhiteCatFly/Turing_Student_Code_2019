#include "head.h"
using namespace std;


crawl::crawl(string root_)
{
    n = 0;
    this->root=root_;
};

crawl::~crawl()
{
    std::cout << "DONE!" << std::endl;
};

void crawl::BFS()
{
    current = root;
    todo.push(current);

    while (!todo.empty())
    {
        current = todo.front();
        todo.pop();
        cout<<todo.size()<<endl;
        
        done.insert(current);
        
        string content = getcontent();

        set<string> urls;
        parse(content, urls);

        for (auto x : urls)
        {
            if (done.find(x) == done.end())
            {

                todo.push(x);
                //done.insert(x);
            }
        }
    }
}
