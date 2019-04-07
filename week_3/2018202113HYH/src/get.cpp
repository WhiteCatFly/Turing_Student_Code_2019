#include "get.h"


std::string get::get_content()             //获得网页内容
{

    std::ifstream fin;

    total_urls++;
    std::cout << total_urls << std::endl;
    
    std::string content;
    std::string line;

    std::string order = "wget --timeout=3 --waitretry=0 --tries=5 \"";
    std::string opn   = "\" -O ";
    //std::string file  = "/home/halcyon/index.html";
    
    opn   += storage_path;
    order += current;
     
    order += opn;
    //cout<< order <<endl;
    system (order.c_str());

    fin.open(storage_path);
    //cout<<fin.is_open(opn)<<endl;
    while (getline(fin,line))
        content += line;

    fin.close();

    return content;

}