#include <fstream>
#include <iostream>
#include <string>

#include "Crawler.h"
#include "Fetcher.h"
#include "Config.h"

Crawler crawler;
Fetcher fetcher;

libconfig::Config cfg;

std::string rootUrl;
std::string FOUT_FILENAME, 
            FERR_FILENAME, 
            FLOG_FILENAME,
            SAVE_PATH;
std::ifstream fin,
              fwaiting;
std::ofstream fout, 
              ferr,
              flog;

int MAX_FAIL_TIME, MAX_EASY_TIME, MAX_EASY_NUM;

void init0()
{
    if(initConfig(cfg) == EXIT_FAILURE)
        exit(0);

    SAVE_PATH = getStringConfig(SAVE_PATH);

    FOUT_FILENAME = getStringConfig(FOUT_FILENAME);
    FERR_FILENAME = getStringConfig(FERR_FILENAME);
    FLOG_FILENAME = getStringConfig(FLOG_FILENAME);

    rootUrl = getStringConfig(rootUrl);
    if(rootUrl[rootUrl.size() - 1] != '/') 
        rootUrl += '/';

    MAX_FAIL_TIME = getIntConfig(MAX_FAIL_TIME);
    MAX_EASY_TIME = getIntConfig(MAX_EASY_TIME);
    MAX_EASY_NUM = getIntConfig(MAX_EASY_NUM);
}

void initC1()
{
    fin.open(FOUT_FILENAME);
    fwaiting.open(FLOG_FILENAME);
}

void initC2()
{
    fin.close();
    fwaiting.close();
    fout.open(FOUT_FILENAME, std::ofstream::out | std::ofstream::app);
    ferr.open(FERR_FILENAME, std::ofstream::out | std::ofstream::app);
    flog.open(FLOG_FILENAME, std::ofstream::out | std::ofstream::app);
}

void initN1()
{
    fout.open(FOUT_FILENAME);
    ferr.open(FERR_FILENAME);
    flog.open(FLOG_FILENAME);
}

void cleanup()
{
    fout.close();
    ferr.close();
    flog.close();
}

int main(int argc, char *argv[])
{
    init0();
    bool continueFlag = 0;
    int pageCount = 0;

    for(int i = 0; i < argc; i++)
        if(std::string(argv[i]) == "-c")
        {
            continueFlag = 1;
            break;
        }

    if(continueFlag)
    {
        initC1();
        crawler = Crawler(fin, fwaiting, pageCount);
        std::cout << "Last time : " 
                  << pageCount << "page(s).\n";
        initC2();
    }
    else
    {
        initN1();
        crawler = Crawler(rootUrl);
    }

    while(!crawler.empty())
    {   
        auto batch = crawler.getNextBatch();
        auto responses = fetcher.fetchBatch(batch);
        int tmpCount = 0;
        for(auto &r : responses)
        {
            crawler.setResponse(r.url, r.text);
            crawler.parseHTML(r.url, r.text);
            tmpCount += !r.text.empty();
        }
        pageCount += tmpCount;
        std::cout << "New : " << tmpCount
                  << "   Total : " << pageCount 
                  << " page(s)."
                  << std::endl;
    }
    std::cout << "Total : " 
              << pageCount << " page(s)."
              << std::endl;
    cleanup();   
}