#include <iostream>
#include <dirent.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <functional>

#include "Library.h"
#include "DOM.h"
#include "search.h"
#include "Document.h" 

double Library::scoreDocument(std::vector<std::string> &queryTerms, Document &d)
{
    double score = 0.0;
    for(int i = 0; i < queryTerms.size(); i++)
        score += IDF[queryTerms[i]] * d.queryTF(queryTerms[i]) * pow(0.95, i);
    return score;
}

void Library::showResult(std::vector<std::pair<int, double> > &result)
{
    int num = 0;
    for(auto it : result)
    {
        num++;
        std::cout << "Result #" << num << std::endl
                  << "[ Relevance ] " << it.second 
                  << std::endl;
        file[it.first].show();
        std::cout << std::endl;
    }
}

bool emergency_ends_with(std::string a, std::string patt)
{
    if (a.length() < patt.length())
        return false;
    for (int i = 0; i < patt.length(); i++)
        if (a[a.length() - i] != patt[patt.length() - i])
            return false;
    return true;
}

Library::Library(std::string dir)
{
    fileNum = 0;
    std::vector<std::string> files;
    getFiles(dir.c_str(), files);

    int counter = 0;
    for(auto it : files) {
        addDocument(it);
        double percentage = double(++counter) / files.size() * 100;
        printf("Loading... %.2lf%%          \r", percentage);
        fflush(stdout);
    }
    buildIDF();
    printf("Loading... done          \n");
}

void Library::addDocument(std::string filename)
{
    std::ifstream fin(filename);
    DOM dom(fin);
    fin.close();
    Document d(++fileNum, filename, dom.extractAllText());
    file[fileNum] = d;
}

void Library::buildIDF()
{
    for(auto it : file)
    {
        std::vector<std::string> terms = std::move(it.second.getTerms());
        for(int i = 0; i < terms.size(); i++)
            IDF[terms[i]]++;
    }
    for(auto it : IDF)
        IDF[it.first] = log10((fileNum + 1) / (1 + it.second));
    for(auto it : file)
    {
        std::vector<std::string> terms = it.second.getTerms();
        for (auto& term : terms)
            file[it.first].setIDF(term, IDF[term]);
        file[it.first].sortTerms();
    }
}

void Library::query(std::string str, int num)
{    
    std::vector<std::string> queryTerms = search(str);
    std::function<bool(const std::string&, const std::string&)> cmpTerm =
    [this](const std::string& a, const std::string &b)
    {
        if (this->IDF[a] == this->IDF[b])
            return a > b;
        return this->IDF[a] > this->IDF[b];
    };
    
    sort(queryTerms.begin(), queryTerms.end(), cmpTerm);
    std::vector<std::pair<int, double> > score;
    for(int i = 0; i < file.size(); i++)
        score.push_back({i, scoreDocument(queryTerms, file[i])});
    sort(score.begin(), score.end(), cmpScore);
    while(score.size() > num) 
        score.pop_back();
    showResult(score);
}

void getFiles(const char *basePath, std::vector<std::string> &files)
{
    DIR *dir;
    struct dirent *ptr;
    char base[1000];

    if ((dir=opendir(basePath)) == NULL)
        return;
    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
        {
            std::string filename = (std::string)basePath + '/' + (std::string)ptr->d_name;
            files.push_back(filename);
        }
        else if(ptr->d_type == 4)    ///dir
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,basePath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            getFiles(base, files);
        }
    }
    closedir(dir);
}

bool cmpScore(std::pair<int, double> a, std::pair<int, double> b)
{
    return a.second > b.second;
}
