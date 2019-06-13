#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#include "Document.h"
#include "search.h"

Document::Document(int index_, std::string url_, std::string rawText_)
{
    index = index_;
    url = url_;
    rawText = rawText_;
    terms = std::move(search(rawText_));
    for(auto& it :terms)
        TF[it] += 1.0;
    for(auto& it : TF)
        TF[it.first] /= terms.size();   
    // unique terms
    std::set<std::string> terms_uq;
    for(auto& term : terms)
        terms_uq.insert(term);
    terms.clear();
    for(auto& term : terms_uq)
        terms.push_back(term);
    sortTerms();
}

void Document::sortTerms()
{
    std::vector<std::pair<double, std::string>> tmp; 
    for(auto& term : terms)
        tmp.push_back(make_pair(- this->TF[term], term));
    sort(tmp.begin(), tmp.end());
    terms.clear();
    for(auto& pr : tmp)
        terms.push_back(pr.second);
    return;
}

double Document::queryTF(std::string term)
{
    if(TF.find(term) == TF.end()) 
        return 0.0;
    return TF[term];
}

std::vector<std::string> Document::getTerms()
{
    return terms;
}

void Document::show(int num, int len)
{
    // Url
    std::cout << "[ Url ] " << url << std::endl;
    // Keywords
    std::cout << "[ Keywords ] ";
    for(int i = 0; i < terms.size() && num; i++)
    {
        std::cout << terms[i] << " ";
        num--;
    }
    std::cout << std::endl;
    // View
    std::cout << "[ View ] " << std::endl;
    std::cout << rawText.substr(0, len) << std::endl;
}

void Document::setIDF(const std::string& term, double IDF)
{
    TF[term] *= IDF;
}
