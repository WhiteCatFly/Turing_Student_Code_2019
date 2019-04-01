#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <set>
#include <queue>
#include <iostream>
#include <fstream>


class get;
class work;
class search;

void if_find(work & work, search & search);

class search
{
    
    public:
    friend class get;
    friend class work;
    friend void if_find(work & work,search & search);
    search()
    {

    }
    search(std::string root_)
    {
        urls_tobe_clawed.push(root_);
        root = root_;
    }
    
    void bfs(get & get, work & work, search & search);
    //void if_find();
    ~search()
    {

    }


    private:
    
    std::queue <std::string> urls_tobe_clawed;
    std::set   <std::string> urls_clawed;
    std::string root;
    std::ofstream fout;
    
    
};



#endif
