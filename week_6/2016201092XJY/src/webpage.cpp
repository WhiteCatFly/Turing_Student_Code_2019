#include "webpage.h"

using std::string;
using std::to_string;
using std::ifstream;
using std::regex;
using std::sregex_iterator;
using std::cout;
using std::endl;

int WebPage::_count = 0;
set <string> WebPage::_urlAlreadyBeCrawled{};
queue <string> WebPage::_urlToBeCrawled{};

void WebPage::setURL(const string & url){
    _url = url;
}

void WebPage::setDownloadPath(){
    _downloadPath = "File/" + to_string(_count);
}

void WebPage::downloadURL() const {
    string order = "wget -O " + _downloadPath + " --reject=doc,docx,pdf "  + _url  ;
    system(order.c_str());
}

void WebPage::getSourceCode(){
    downloadURL();

    ifstream fin(_downloadPath);
    string content, temp;
    while(getline(fin,temp))
    {
        temp += "\n";
        content += temp;
    }
    _sourceCode = content;
}

void WebPage::parseURLs(){
    _urlsCurrentPage = Parser.getAllUrls();

    for (auto url : _urlsCurrentPage)
    {
        if (url.find("&&") != url.npos){        // Very Important, & is a special char which cannot be recognized by wget function
            url = url.insert(url.find("&&"), "\\" );
            url = url.insert(url.find("&&")+1, "\\" );
        }
        if (url.find("http") == 0)       // If "http" found at position 0
        {
            if ( (url.find(_url) != 0) )

                continue;
            }
            else{
                if ( (url.find(".htm") == url.npos) && (url.find(".php") == url.npos) )
                {
                    continue;
                }
            }
        }
        else
        {
            if  ( (url.find(".htm") == url.npos) && (url.find(".php") == url.npos) )
            {
                continue;
            }
            else
            {
                url = _url + url;
            }
        }

        _urlsCurrentPage.insert(url);
    }
}

void crawl(const string & root)
{
    WebPage::_urlToBeCrawled.push(root);

    while (!WebPage::_urlToBeCrawled.empty())
    {
        string cr = WebPage::_urlToBeCrawled.front();  //cr for current_url
        WebPage WP(cr);
        WebPage::_urlToBeCrawled.pop();
        WebPage::_urlAlreadyBeCrawled.insert(cr);

        for(auto url : WP._urlsCurrentPage){
            if (WebPage::_urlAlreadyBeCrawled.count(url) == 0)
            {
                WebPage::_urlToBeCrawled.push(url);
                WebPage::_urlAlreadyBeCrawled.insert(url);    //  IMPORTANT STEP
            }
        }

        cout << WebPage::_urlAlreadyBeCrawled.size() << "||" <<  WebPage::_urlToBeCrawled.size() << endl;

        /*if (WP.getCount() == 50){     // Test
            break;
        }*/
    /*for (auto i : WebPage::_urlAlreadyBeCrawled){
        cout << i << endl;
    }*/
    }
}

