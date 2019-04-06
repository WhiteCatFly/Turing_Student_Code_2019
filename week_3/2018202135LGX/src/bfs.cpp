#include"crawler.h"

void Crawler::bfs(){

    while(!temp_results.empty()){

        GetContent();

        ParseURLs();

        current_url = temp_results.front();

        temp_results.pop();

        fout << current_url << std::endl;

        index ++;
    }
}

