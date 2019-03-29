#include <iostream>
#include <fstream>
#include <string>

#include "bfs.h"

int main(int argc, char *argv[])
{
    std::string err_file = "error.txt",
                suc_file = "success.txt";

    if(argc >= 2)
        err_file = argv[1];
    if(argc >= 3)
        suc_file = argv[2];
    
    ferr.open(err_file);
    fout.open(suc_file);

    bfs();
  
    ferr.close();
    fout.close();

}