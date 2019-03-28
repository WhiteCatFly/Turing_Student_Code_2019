#include <string>
#include <ctime>
#include "HTMLFunc.h"
#include "getContent.h"
#include "crawl.h"

using std::string;
using std::cout;
using std::endl;
using std::time_t;

int main()
{
    time_t start = time(NULL);
    // string seed = "http://info.ruc.edu.cn/";
    crawl();
    time_t finish = time(NULL);
    cout << "Run Time: " << (double)(finish-start) << "s" << endl;
    return 0;
}
