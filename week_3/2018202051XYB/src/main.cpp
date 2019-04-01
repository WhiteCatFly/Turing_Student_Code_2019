#include <fstream>
#include <iostream>
#include <string>

#include "my_crawler.h"
#include "my_fetcher.h"
#include "my_config.h"

my_crawler crawler;
my_fetcher fetcher;

libconfig::Config cfg;

std::string root_url;
std::string FOUT_FILENAME, FERR_FILENAME, SAVE_PATH;
std::ofstream fout, ferr;

int MAX_FAIL_TIME, MAX_EASY_TIME, MAX_EASY_NUM;

void init()
{
    if(config_init(cfg) == EXIT_FAILURE)
        exit(0);

    SAVE_PATH = get_string_config(SAVE_PATH);

    FOUT_FILENAME = get_string_config(FOUT_FILENAME);
    FERR_FILENAME = get_string_config(FERR_FILENAME);

    fout.open(FOUT_FILENAME);
    ferr.open(FERR_FILENAME);

    root_url = get_string_config(root_url);
    if(root_url[root_url.size() - 1] != '/') 
        root_url += '/';

    MAX_FAIL_TIME = get_int_config(MAX_FAIL_TIME);
    MAX_EASY_TIME = get_int_config(MAX_EASY_TIME);
    MAX_EASY_NUM = get_int_config(MAX_EASY_NUM);

}

void cleanup()
{
    fout.close();
    ferr.close();
}

int main()
{
    
    init();

    int page_count = 0;

    crawler.init(root_url);
    while(!crawler.empty())
    {   
        auto batch = crawler.get_next_batch();
        auto responses = fetcher.fetch_batch(batch);
        int tmp_count = 0;
        for(auto &r : responses)
        {
            crawler.set_response(r.url, r.text);
            crawler.parse_html(r.url, r.text);
            tmp_count += !r.text.empty();
        }
        page_count += tmp_count;
        std::cout << "New : " << tmp_count
                  << "   Total : " << page_count 
                  << std::endl;
    }
    std::cout << "Total : " << page_count << std::endl;

    cleanup();   
}

