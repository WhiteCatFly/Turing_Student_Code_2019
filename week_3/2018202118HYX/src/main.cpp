#include "head.h"
#include<ctime>
using namespace std;


int main()
{
    clock_t start,end;
    start=clock();

    string root="econ.ruc.edu.cn";
    crawl run(root);
    run.BFS();
    
    end=clock();
    cout<<double(end-start)/CLOCKS_PER_SEC;
    
    return 0;
}
