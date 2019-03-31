#include "tools.h"

int main()
{   
    clock_t start,finish;
    start = clock();

    std::string root = "econ.ruc.edu.cn";
    std::string path;
 
    get econ;
    work operate;
    search search(root);

    std::cout << "please enter the storage path: " << std::endl;
    std::cin  >> path;
    econ.get_path(path);

    search.bfs( econ , operate , search);
    
    int total_urls = econ.get_num();

    finish = clock();
    double total_time;
    total_time = (double)(finish - start) / CLOCKS_PER_SEC;

    std::cout << "total time :" << time << "seconds" << std::endl;
    std::cout << "total urls :" << total_urls << std::endl;
    return 0;
}