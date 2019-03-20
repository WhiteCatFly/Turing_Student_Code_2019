#include <iostream>
#include <set>
#include <queue>
#include <fstream>
#include "getContent.h"
#include "HTMLFunc.h"
#include "crawl.h"

using std::string;
using std::queue;
using std::set;
using std::cout;
using std::endl;
using std::to_string;

void crawl(const string & root)
{
    queue   <string>    url_to_be_crawled;
    set     <string>    url_already_be_crawled;
    set     <string>    urls_current_page;

    url_to_be_crawled.push(root);

    int count = 0 ;

    while (!url_to_be_crawled.empty())
    {
        string cr = url_to_be_crawled.front();  //cr for current_url
        url_to_be_crawled.pop();
        url_already_be_crawled.insert(cr);

        string dir = "File/" + to_string(count);
        parseURLs(getContent(cr,dir), cr, urls_current_page);

        for(auto url : urls_current_page){
            if (url_already_be_crawled.count(url) == 0)
            {
                url_to_be_crawled.push(url);
                url_already_be_crawled.insert(url);    //  IMPORTANT STEP
            }
        }

        cout << url_already_be_crawled.size() << "||" <<  url_to_be_crawled.size() << endl;

        count ++;

        /*if (count == 100){
            break;
        }*/

    }


    cout << url_already_be_crawled.size() << endl;

    int j = 0;
    set <string> test;
    int size = (int)url_to_be_crawled.size();
    while (j < size){
        string A = url_to_be_crawled.front();
        url_to_be_crawled.pop();
        test.insert(A);
        j++;
    }
    cout << j << "???" << test.size() << endl;
}

