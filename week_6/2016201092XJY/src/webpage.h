#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <fstream>
#include <regex>
#include "HTMLParser.h"

using std::string;
using std::set;
using std::queue;

class WebPage{
    friend void crawl(const string & root);
    private:
        static int _count;
        static set <string> _urlAlreadyBeCrawled;
        static queue <string> _urlToBeCrawled;
        string _url;
        string _downloadPath;
        string _sourceCode;
        set <string> _urlsCurrentPage;
	HTMLParser Parser("");

        void setURL(const string & url);
        void setDownloadPath();
        void downloadURL() const ;
        void getSourceCode();
        void parseURLs();
    public:
        WebPage(const string & url)
        {
            _count++ ;

            setURL(url);
            setDownloadPath();
            getSourceCode();
	    Parser(_sourceCode);
            parseURLs();
        }
        static int getCount(){
             return _count;
        }
};

void crawl(const string & root = "http://econ.ruc.edu.cn/");

#endif

