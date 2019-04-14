#include "getContent.h"

using std::string;
using std::ifstream;

void downloadURL(const string & url,const string & dirname)
{
    string order = "wget -O " + dirname + " --reject=doc,docx,pdf "  + url  ;
    system(order.c_str());
}

string getContent(const string & url,const string & dirname)
{
    downloadURL(url,dirname);

    ifstream fin(dirname);
    string content, temp;
    while(getline(fin,temp))
    {
        temp += "\n";
        content += temp;
    }
    return content;
}
