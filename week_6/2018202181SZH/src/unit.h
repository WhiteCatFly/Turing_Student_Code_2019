#ifndef UNIT_H
#define UNIT_H
#include<iostream>
#include<string>
#include<set>
#include<queue>
#include<fstream>
#include<algorithm>
#include<sstream>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
void input_first_url(string &url);
class WEB{
    private:
        string current_url;
    public:
        WEB(){};
        ~WEB(){};
        string getContent(int times);
        void getString(string& url){
            this->current_url = url;
        }
};
class website {
    private:
        std::queue<string>url_to_be_crawled;
        std::set<string>url_already_be_crawled;
        int n;
        string current_url;
        void parseUrls(string &src,std::set<string> &store);
        WEB WEB_site;

    public:
        website();
        ~website();
        void Bfs( );
        void set_n(int num){
            n = num;
        }
        void restart(string to_be_txt,string already_txt);
};
class html;
class website_html{
    friend void judge_url_or_file(string &line,html &web);

    protected:
        string html_code, origin_url, store_place;
    public:
        website_html();
        ~website_html(){};
};
class html : public website_html{
    public:
        html(){};
        ~html(){};
        void get_url() const;
        void get_title() const;
        void get_main_txt() const;
        void get_certain_pattern(string &type)const;
        void inter_face()const; 
        void continue_interface()const;
};
#endif // UNIT_H
