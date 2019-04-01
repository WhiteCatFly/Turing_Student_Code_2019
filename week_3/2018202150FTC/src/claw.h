#include <regex>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <string.h>
#include<sstream>
#include<string.h>
 using namespace std;

class StringUtils
{
public:
    static double str2Double(const std::string & s);
        //字符串转double，以下类似
    static std::string double2Str(double d);
    static int str2Int(const std::string & s);
    static std::string int2Str(int i);
};



class spider{
    public:
    spider()=default;
    spider(std::string _root="econ.ruc.edu.cn"){
        std::cout<<_root<<" is coming"<<std::endl;
        root=_root;
        tobe.push(root);
    }
    ~spider(){
        std::cout<<"the spider is finished"<<std::endl;

    }
    
    std::string current;
    std::string content;
    std:: set<std::string> urls;
    std::set<std::string> clawed;
    std::queue<std::string> tobe;

    inline void shownumber() const{
        std::cout<<cnt;
    }
    void bfs();
    std::string get_content(const std::string & _current);
    void parse(std::string & content, std::string & current,std::set<std::string> & urls);

    int get_urls(const std::string & res,std::set<std::string> & urls,std::string & current,int mode);
    private:
    std::string root;
    int cnt=0;
    bool state=true;


    

    


};

