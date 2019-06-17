#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <string>
#include <iostream>
#include <map>

#include "Document.h"
class Library
{
private:
    int fileNum;
    std::map<int, Document> file;
    std::map<std::string, double> IDF;
    double scoreDocument(std::vector<std::string> &queryTerms, Document &d);
    void showResult(std::vector<std::pair<int, double> > &result);
public:
    Library(std::string dir);
    Library() = default;
    void addDocument(std::string filename);
    void buildIDF();
    void query(std::string str, int num = 10);
};

void getFiles(const char *basePath, std::vector<std::string> &files);

bool cmpScore(std::pair<int, double> a, std::pair<int, double> b);

#endif