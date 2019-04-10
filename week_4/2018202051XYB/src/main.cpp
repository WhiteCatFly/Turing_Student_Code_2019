#include <iostream>
#include <fstream>


#include "Token.h"
#include "DOM.h"

int main(int argc, char *argv[])
{
    std::ifstream fin(argc > 1 ? std::string(argv[1]): "example.html");

    DOM DOMTree(fin);
    DOMTree.showTree();

}