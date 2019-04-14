#include "HTMLParser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
int main(int argc,char *argv[])
{
    std::string website;
    char * filename;
    if(argc > 2)
    {
        filename = argv[1];
        website = argv[2];
    }
    else
    {
        website = "info.ruc.edu.cn/index.php/";
        filename = "0.html";
    }
    Parser parser(filename,website);
    parser.Title();
    std::cout << "stop" << std::endl;
    parser.Body();
    return 0;
}