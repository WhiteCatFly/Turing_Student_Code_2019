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
    inline Htmlparser(std::string name){
        source=name;
        mode=1;}
    inline Htmlparser(std::fstream file){file>>content;
    mode=2;}
    Htmlparser()=default;
    void readin();
    void gettitle();
    void getpara();
    void getpic();
    void geturl();
    std::string show(){return source;}

};