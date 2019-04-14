#include <regex>
#include<vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
class Htmlparser{
    private:
    int mode;
    std::string source;
    std::string content;
    public:
     Htmlparser(std::string name);
    inline Htmlparser(std::fstream file){file>>content;
    mode=2;
     std::cout<<"if you want title, press 1,and find it on title.txt"<<std::endl;
        std::cout<<"if you want picture press 2 and find it on picture.txt"<<std::endl;
        std::cout<<"if you want urls press 3 and find it on url.txt"<<std::endl;
        std::cout<<"if you want paragraph press 4 and find it on paragraph.txt"<<std::endl;
        std::cout<<"if you don't want anymore,press 0"<<std::endl;
        readin();}
    Htmlparser()=default;
    void readin();
    void gettitle();
    void getpara();
    void getpic();
    void geturl();
    void interface();
    std::string show(){return source;}

};