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
    regex pattern("href=(\"[^\"]+\"|'[^']+'|[^\\s>)]+)");
    //regex pattern("href\s*=\s*(?:\"([^\"]*)\"|\'([^\']*)\'|([^\"\'>\s]+))");
    string head ="herf=";

    for (sregex_iterator it(_sourceCode.begin(), _sourceCode.end(), pattern) , end;
        it != end;
        ++it)
    {
        string now = it->str();
        if (now.find("&&") != now.npos){        // Very Important, & is a special char which cannot be recognized by wget function
            now = now.insert(now.find("&&"), "\\" );
            now = now.insert(now.find("&&")+1, "\\" );
        }
        string nownew;
        if ( (now.find("=\"") != now.npos) || (now.find("=\'") != now.npos) ){
            nownew = now.substr( head.length()+1, now.length() - head.length() - 2 );
        }
        else {
            nownew = now.substr( head.length(), now.length() - head.length()  );
        }

        if (nownew.find("http") == 0)       // If "http" found at position 0
        {
            if ( (nownew.find("http://econ.ruc.edu.cn") != 0) )
            {
                continue;
            }
            else{
                if ( (nownew.find(".htm") == nownew.npos) && (nownew.find(".php") == nownew.npos) )
                {
                    continue;
                }
            }
        }
        else
        {
            if  ( (nownew.find(".htm") == nownew.npos) && (now.find(".php") == nownew.npos) )
            {
                continue;
            }
            else
            {
                nownew = "http://econ.ruc.edu.cn/" + nownew;
            }
        }

        _urlsCurrentPage.insert(nownew);
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

