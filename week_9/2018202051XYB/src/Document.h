#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include <string>
#include <set>
#include <vector>
#include <map>

class Document
{
private:
    int index;
    std::string rawText;
    std::string url;
    std::map<std::string, double> TF;
    std::vector<std::string> terms;
public:
    Document(int index_, std::string url_, std::string rawText_);
    Document() = default;
    void sortTerms();
    double queryTF(std::string term);
    std::vector<std::string> getTerms();
    void show(int num = 10, int len = 500);
    void setIDF(const std::string& term, double IDF);
};


#endif