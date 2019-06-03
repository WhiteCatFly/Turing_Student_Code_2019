#include<sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<utility>
#include<cmath>
#include<algorithm>

class Htmlparser{
    private:
    std::string source;
    std::string content;
    int no;
    public:
    Htmlparser(int _no);
    Htmlparser(std::string name);
    Htmlparser()=default;
    void readin();
    std::string gettitle();
    void getpara();
    void getpic();
    void geturl();
    void current_url();
    void interface();
    std::string show(){return source;}

};