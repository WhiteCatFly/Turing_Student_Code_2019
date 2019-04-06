#include"head.h"
using namespace std;

string crawl::getcontent()
{
    n++;

    string file = to_string(n)+".html";
    
    if(current.find(root) == current.npos )
    {
        if(n != 1)
        {
            if(current[0] == '/')
                current = root  + current;
            else
                current = root + '/' + current;
        }
    }   
    
    string order = "wget -O "+file+"  "+'\"'+current+'\"';

    system(order.c_str());

    ifstream fin ;
    fin.open(file);
    string line,content;
    while(getline(fin,line)){
        content+=line;
    }
    fin.close();
    return content;
}