#include "parser.h"


int main()
{
    parser my_parser;
    std::string root  ;
    std::string order ;
    std::string storage_path ;
    //std::stringstream ss();

    std::cout << "please enter the root" << std::endl;
    std::cin  >> root;
    my_parser.set_root(root);
    my_parser.get_content();

    std::cout << "please enter what you want to find" << std::endl;
    std::cout << "you have 3 options" << std::endl;
    std::cout << "1 title" << std::endl;
    std::cout << "2 body" << std::endl;
    std::cout << "3 url" << std::endl;
    std::cout << "please use the words above" << std::endl;
    
    std::cin  >> order ;
    std::cout << "please enter the storage path of the data" << std::endl;
    std::cin  >> storage_path ;
    my_parser.set_fout(storage_path);

    if(order == "title")
    {
        my_parser.get_title();
    }
    else if(order == "body")
    {
        my_parser.get_body();
    }
    else if(order == "url")
    {
        my_parser.get_urls();
    }

    std::cout << "mission complete" << std::endl;

    return 0;

}