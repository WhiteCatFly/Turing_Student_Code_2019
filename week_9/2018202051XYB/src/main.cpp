#include <iostream>
#include <fstream>

#include "Library.h"
#include "DOM.h"

int main()
{
    Library lib("download");
    while(1)
    {
        std::string queryStr;
        std::cout << ">>> ";
        std::cin >> queryStr;
        if(queryStr == "q")
            break;
        lib.query(queryStr);
    }
    return 0;
}