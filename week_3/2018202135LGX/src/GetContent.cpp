#include"crawler.h"

void Crawler::GetContent(){

    web_content.clear();

    if(current_url.empty()) return;

    std::string syscmd = "wget -O " + temp_filename + " --timeout=2 --tries=2 " + "-c " + current_url;

    int m = system(syscmd.c_str());

    std::ifstream fin;

    fin.open(temp_filename);

    int k = 0;

    while(!fin.eof()){

        web_content += fin.get();

        k ++;

        if(k > 1024 * 1024){

            break;
            
        }  

    }

    fin.close();

    syscmd = "rm " + temp_filename;
    
    if(m == 0)

    system(syscmd.c_str());
}