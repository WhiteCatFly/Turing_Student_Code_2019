#include "crawler.h"
#include "parser.h"

int main(int argc,char *argv[])
{
    string root;

    if(argc == 1)
    {
        std::cout << "please enter the root :" << std::endl;
        std::cin  >> root ;
         
        crawler my_crawler(root);

        run_bfs(my_crawler);

    }
    else if(argc = 2)               // argv[1] == "end"
    {
        crawler my_crawler;

        my_crawler.delete_record();
    }
    else if(argc == 3)               //argv[1] == "restart" argv[2] == root
    {
        root = argv[2]; 
        crawler my_crawler(root);

        run_bfs(my_crawler);

    }
   
   
    

    return 0;
}