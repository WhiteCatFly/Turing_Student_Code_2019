#include <iostream>
#include <ctime>
#include "webpage.h"

using std::cout;
using std::endl;
using std::time_t;

int main(int argc, char* argv[])
{
    time_t start = time(NULL);
    crawl();   // Default: "http://econ.ruc.edu.cn/"
    time_t finish = time(NULL);
    cout << "Run Time: " << (double)(finish-start) << "s" << endl;
    return 0;
}
