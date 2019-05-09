#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "normalize.h"
#include "htmlparser.h"
using namespace std;

int main(int argc, char* argv[])
{
    Parser p;
    if (argc > 1)
    {
        string s = argv[1];
        if (s == "--parse")
        {
            if (argc <= 4)
            {
                cerr << "wrong command-line argument" << endl;
                return 0;
            }
            p.init(argv[2], argv[3][0] - '0', argv[4], 1, 0);
        }
        else if (s == "--crawl")
        {
            if (argc <= 2)
            {
                cerr << "wrong command-line argument" << endl;
                return 0;
            }
            string name = filename(argv[2]);
            p.init(argv[2], 3, name, 0, 1);
        }
        else
        {
            cerr << "wrong command-line argument" << endl;
            return 0;
        }
    }
    else
    {
        int tmp;
        cout << "What do you want to do?\n 0 : parse 1 : crawl" << endl;
        cin >> tmp;
        if (tmp == 0)
        {
            string website, name;
            int type;
            cout << "Please input the website, parse type and savefile name\n type : 1 : title, 2 : text, 3 : link, 4 : custom(use regex)" << endl;
            cin >> website >> type >> name;
            p.init(website, type, name, 1, 0);
        }
        else
        {
            string website, name;
            cout << "Please input the website" << endl;
            cin >> website;
            name = filename(website);
            p.init(website, 3, name, 0, 1);
        }
    }
    int tmp = p.set_type();
	while (!tmp) tmp = p.set_type();
    p.parse();
    p.print_parser();
    p.crawl();
    p.print_crawler();
	return 0;
}