#include "HTMLFunc.h"

using std::string;
using std::set;
using std::sregex_iterator;
using std::regex;

void parseURLs(const string & page_content, const string & current_url, set <string> &urls_current_page)
{
    regex pattern("a href=\".*?(?=\")");
    string head ="a herf=\"";

    for (sregex_iterator it(page_content.begin(), page_content.end(), pattern) , end;
        it != end;
        ++it)
    {
        string now = it->str();
        now = now.substr(now.find(head) + head.length() + 1, now.length() - now.find(head));

        if (now.find("http://") == 0)
        {
            if ( (now.find("http://info.ruc.edu.cn") != 0)|| (now.find("#") != now.npos) || (now.find(".doc") != now.npos) || (now.find(".pdf") != now.npos) || (now.find("&") != now.npos) )
            {
                continue;
            }
        }
        else
        {
            if  ( (now.find("@") != now.npos) || (now.find("#") != now.npos) || (now.find(".doc") != now.npos) || (now.find(".pdf") != now.npos) || (now.find("&") != now.npos) )
            {
                continue;
            }
            else
            {
                now = "http://info.ruc.edu.cn/" + now;
            }
        }


       /* if (now[0] != '/')
        {
            if (current_url.find_last_of('/') != current_url.length()-1 )
            {
                now = current_url.substr(0,current_url.find_last_of('/')) + now;
            }
            else if (now.find("http://") == 0)
            {
                if (now.find("http://info.ruc.edu.cn") == 0)
                {
                    continue;
                }
            }
            else
            {
                now = current_url + now;
            }
        }
        else
        {
            now = "http://info.ruc.edu.cn" + now;
        }
*/
        urls_current_page.insert(now);
    }
}

