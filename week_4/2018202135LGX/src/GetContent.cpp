#include"HTMLparser.h"

void HTMLparser::GetContent(){

    std::string syscmd = "wget -O temp --timeout=2 --tries=2 -c " + host;

    int m = system(syscmd.c_str());

    std::ifstream fin;

    fin.open("temp");

    int k = 0;

    while(!fin.eof()){

        web_content += fin.get();

        k ++;

        if(k > 1024 * 1024){

            break;
            
        }  

    }

    web_content.pop_back();

    fin.close();

    syscmd = "rm temp";
    
    if(m == 0)

    system(syscmd.c_str());
}