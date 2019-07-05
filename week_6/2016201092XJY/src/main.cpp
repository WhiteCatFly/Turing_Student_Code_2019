#include <iostream>
#include <ctime>
#include "webpage.h"

using std::cin;
using std::cout;
using std::endl;
using std::time_t;

int main(int argc, char* argv[])
{
    string url;
    cout << "Please enter the URL you'd like to crawl:" << endl;
    cin >> url;
    time_t start = time(NULL);
    crawl(url);   // Default: "http://econ.ruc.edu.cn/"
    time_t finish = time(NULL);
    cout << "Run Time: " << (double)(finish-start) << "s" << endl;
    return 0;
}
