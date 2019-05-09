#ifndef CRAWLER_H
#define CRAWLER_H

#include<iostream>
#include<string>
#include<set>
#include<queue>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<regex>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
 
void input_first_url(std::string &url);

class craw
{
private:
    string current_url;
public:
    craw(){};
    ~craw(){};
    string getContent(int times);
    void getString(string& url){
        this->current_url = url;
    }
};

class crawler 
{
private:
    std::queue<std::string> to_be;
    std::set<std::string> already;
    int n;
    std::string current_url;
    void parseUrls(std::string &src,std::set<std::string> &store);
    craw craw_website;
public:
    crawler();
    ~crawler();
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

class Parser : public website_html{
private:
    std::string Source_Code;
    static std::set<std::string> Label_Key;
    static std::string Big_Small_Same(std::string s);
    void Output(const std::string &code, int tabs, std::ostringstream &ostr);
    void Process();
public:
    Parser(const char *filename);
    Parser(const std::string &code);
    Parser() = default;
    int Extract(const std::regex &reg, std::vector<std::string> &result);
    int Get_Title(std::vector<std::string> &result);
    int Get_Body(std::vector<std::string> &result);
    int Get_Href(std::vector<std::string> &result);
    int Get_Img(std::vector<std::string> &result);
};
#endif // CRAWLER_H
