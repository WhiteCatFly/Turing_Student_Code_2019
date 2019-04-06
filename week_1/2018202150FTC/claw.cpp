#include "claw.h"

std::string get_content(const std::string & current)
{
    static int cnt = 0;
    using namespace std;
    cnt++;
    char num[10];
    std::ifstream fin;
    string line;
    string order;
    string content;
    string opn;
    int i = 0;
    int temp = cnt;
    while (temp > 0)
    {
        num[i] = temp % 10 + '0';
        temp /= 10;
        i++;
    }
    num[i] = '\0';
    int j = strlen(num) - 1;
    i = 0;
    while (j >= i)
    {
        char tmp;
        tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
        i++;
        j--;
    }

    order = "wget " + current;
    order += " -O ";
    order += num;
    order += ".html";
    cout << "I am order" << ' ' << order << endl;
    char newor[200];
    for (int i = 0; i < order.size(); i++)
        newor[i] = order[i];
    newor[order.size()] = '\0';
    system(newor);
    opn = num;
    opn += ".html";

    fin.open(opn);
    if (fin.is_open())
    {
        cout << "I am fin" << ' ' << opn << endl;
        while (getline(fin, line))
            content += line;
    }
    fin.close();

    return content;
}




void parse(std::string & content, std::string& current,std::set<std::string> & urls)
{
    using namespace std;
    regex regu("href=\"([a-z0-9_:\\/.\\?=]+)\"");
    smatch res;
    while (regex_search(content, res, regu))
    {
        string revise;
        cout << "get in search" << endl;
        cout << res[0].str() << endl;
        cout << res[1].str() << endl;
        if (res[1].str().find("css") != string::npos || res[1].str().find("rss") != string::npos)
        {
            content = res.suffix();
            continue;
        }
        if (res[1].str().find("gif") != string::npos || res[1].str().find("pdf") != string::npos)
        {
            content = res.suffix();
            continue;
        }
        if (res[1].str().find("doc") != string::npos || res[1].str().find("xls") != string::npos)
        {
            content = res.suffix();
            continue;
        }
        if (res[1].str().find(root) != string::npos)
        {
            urls.insert(res[1].str());
            cout << "I get in urls  " << res[1].str() << endl;
        }
        else if (res[1].str()[0] == '/')
        {
            revise = root + res[1].str();
            urls.insert(revise);
            cout << "I get in urls  " << revise << endl;
        }
        else if (res[1].str().find("http") == string::npos)
        {
            revise = root + "/" + res[1].str();
            urls.insert(revise);
            cout << "get in urls" << revise << endl;
        }

        content = res.suffix();
    }
}