#ifndef GET_H
#define GET_H

#include <string>
#include <iostream>
#include <fstream>


class get
{
    public:
     get()
    {
     total_urls=0;
    }

     get(std::string str,int number = 0)
    {   
     total_urls = number;
     current = str;
    }
    void get_path(std::string path)       //改变默认的sterage_path
    {
        storage_path = path;
    }
    void set_current(std::string str)
    {
        current = str;
    }
    std::string get_content();
    int get_num() const         //获得url的总数
    {
        return total_urls;
    }
    ~get()
    {

    }

    private:

     int total_urls;
     std::string current;
     std::string storage_path = "/home/halcyon/index.html";
//std::string storage_path;

};


#endif