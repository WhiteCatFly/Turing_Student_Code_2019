#include"head.h"
using namespace std;

Econ::Econ():Base("econ.ruc.edu.cn")
{  
    econ="econ.ruc.edu.cn";
}

Econ::~Econ()   {   }

void Econ::BFS()
{
    cout<<"BFS"<<endl;
    cout<<"root: "<<econ<<endl;
    todo.push(econ);

    while (!todo.empty())
    {   
        current = todo.front();
        todo.pop();
        
        cout<<"current: "<<current<<endl;
        
        done.insert(current);

        n++;
        string cont;
        if(n>1)
            current=econ+current;

        Get g(current);
        g.getcontent(cont,n);
        //cout<<(*cont)<<endl;
        set<string> urls;
        parse(cont, urls);
        /*set<string>::iterator it=urls->begin();
        for( ; it!=urls->end();it++)
        {
            cout<<*it<<endl;
        }*/
        
        //int num=0;
        for (auto x :urls)
        {
            if (done.find(x) == done.end())
            {
                //num++;
                //cout<<num<<" "<<x<<endl;
                todo.push(x);
            }    
        }
    }
}

Info::Info():Base("info.ruc.edu.cn")
{  
    info="info.ruc.edu.cn";
}

Info::~Info()   {   }

void Info::BFS()
{
    cout<<"BFS"<<endl;
    cout<<"root: "<<info<<endl;
    todo.push(info);

    while (!todo.empty())
    {   
        current = todo.front();
        todo.pop();
        
        cout<<"current: "<<current<<endl;
        
        done.insert(current);

        n++;
        string cont;
        if(n>1)
            current=info+current;

        Get g(current);
        g.getcontent(cont,n);
        //cout<<(*cont)<<endl;
        set<string> urls;
        parse(cont, urls);
        /*set<string>::iterator it=urls->begin();
        for( ; it!=urls->end();it++)
        {
            cout<<*it<<endl;
        }*/
        
        //int num=0;
        for (auto x :urls)
        {
            if (done.find(x) == done.end())
            {
                //num++;
                //cout<<num<<" "<<x<<endl;
                todo.push(x);
            }    
        }
    }
}