#include<fstream>
#include<string>
#include<iostream>
#include<algorithm>
#include<sstream>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class html{
    friend void judge_url_or_file(string &line,html &web);

    private:
        string html_code, origin_url, store_place;
    public:
        html();
        ~html(){};
        void get_url() const;
        void get_title() const;
        void get_main_txt() const;
        void get_certain_pattern(string &type)const;
        void inter_face()const; 
        void continue_interface()const;
};