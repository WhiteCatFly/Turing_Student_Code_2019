#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include<iostream>
#include<string>
#include<set>
#include<fstream>


class HTMLparser{

private:

    std::string web_content;

    std::string title;

    std::string host;

    std::set<std::string> Img;

    std::set<std::string> urls;

    std::string::const_iterator iterStart;

    std::string::const_iterator iterEnd;

    std::string::const_iterator tempiter;

    void GetContent();

public:

    HTMLparser(){};

    HTMLparser(std::string &url){

        host = url;

        GetContent();

        iterStart = web_content.begin();

        iterEnd = web_content.end();

        if(host.find("http") == std::string::npos){

            host = "http://" + host;

        }

    };

    HTMLparser(std::ifstream &fin){

        while(!fin.eof()){

            web_content += fin.get();

        }

        web_content.pop_back();

    };

    void GetTitle();

    void GetBody();

    void GetImg();

    void Ini();

    std::string trans_URLs(std::string aurl, int if_for_img);

    ~HTMLparser(){};

};




#endif


