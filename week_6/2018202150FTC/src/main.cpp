#include "claw.h"
int main(int argc,char* argv[])
{
    if(!(argc>2))
        spider eco=spider("econ.ruc.edu.cn");
    else
    {
        std::string add_flash=(std::string)argv[2];
        int i;
        for(i=0;i<add_flash.size();i++)
            if(add_flash[i]=='/')
            {
                std::string later=add_flash.substr(i);
                add_flash.erase(i);
                add_flash+="/";
                add_flash+=later;
                i++;
            }
        spider eco=spider(argv[1],add_flash);
    }
    
    
}
