#include <string>
#include <vector>
#include <iostream>
#include <cmath>

#include "BM25_valuator.h"
#include "cppjieba/include/cppjieba/Jieba.hpp"

extern cppjieba::Jieba LAC;
extern std::set <std::string> stopWords;
extern std::map <std::string, std::string> synonyms;

void BM25Model::Clear(){
    m_wordToID.clear();
    m_existTimes.clear();
    m_existTimesInFiles.clear();
    m_IDF.clear();
    m_fileLength.clear();
    m_K.clear();
    m_wordInFile.clear();
    m_fileCounter = 0;
    m_totalFileLength = 0;
    m_avgFileLength = 0;
}

void standardize(std::vector<std::string> &x){
    for(auto i = x.begin(); i != x.end(); i++){
        if(stopWords.find(*i) != stopWords.end())
            *i = "";
        else if(synonyms.find(*i) != synonyms.end())
            *i = synonyms[*i];
    }
}

void BM25Model::AddSource(int fileID, std::string x){
    //deal with the file holistically
    m_fileCounter++;
    m_fileLength.push_back(x.size());
    m_totalFileLength += x.size();
    m_wordInFile.push_back(std::map<int,int> ());

    std::vector <std::string> result;
    //deal with every word in the passage
    LAC.CutHMM(x, result);
    standardize(result);

    for(auto i = result.begin(); i != result.end(); i++){
        if(*i == "") continue;
        auto tmpit = m_wordToID.find(*i);
        int size = m_wordToID.size();
        int tmp;
        //allocate position for new word
        
        if(tmpit == m_wordToID.end()){
            tmp = m_wordToID[*i] = size;
            m_existTimes.push_back(0);
            m_existTimesInFiles.push_back(0);
        }else 
            tmp = m_wordToID[*i];
        //counting words
        m_existTimes[tmp] ++;
        m_wordInFile[fileID][tmp] ++;
        if(m_wordInFile[fileID][tmp] == 1)
            m_existTimesInFiles[tmp] ++;
    }

    LAC.CutAll(x, result);
    standardize(result);

    for(auto i = result.begin(); i != result.end(); i++){
        if(*i == "") continue;
        auto tmpit = m_wordToID.find(*i);
        int size = m_wordToID.size();
        int tmp;
        //allocate position for new word
        if(tmpit == m_wordToID.end()){
            tmp = m_wordToID[*i] = size;
            m_existTimes.push_back(0);
            m_existTimesInFiles.push_back(0);
        }else 
            tmp = m_wordToID[*i];
        //counting words
        m_existTimes[tmp] ++;
        m_wordInFile[fileID][tmp] ++;
        if(m_wordInFile[fileID][tmp] == 1)
            m_existTimesInFiles[tmp] ++;
    }

}

void BM25Model::Train(){
//    std::cerr << m_fileCounter << std::endl;
    for(auto i = m_existTimesInFiles.begin(); i != m_existTimesInFiles.end(); i++)
        m_IDF.push_back( log10( (m_fileCounter - (*i) + 0.5) / ( (*i) + 0.5) ));
    m_avgFileLength = m_totalFileLength / m_fileCounter;
    for(auto i = m_fileLength.begin(); i != m_fileLength.end(); i++)
        m_K.push_back( cm_k1 * ( 1 - cm_b + cm_b * (*i) / m_avgFileLength ) );
}

double max(double x, double y){
    return x>y?x:y;
}

/*
needed::

wordtoid
idf
wordinfile
k

 */

double BM25Model::Calculate(int fileID, std::string x){
    std::vector <std::string> result;
    LAC.CutForSearch(x, result);
    standardize(result);
    double tmpans = 0;
    for(auto j = result.begin(); j != result.end(); j++){
        if(m_wordToID.find(*j) == m_wordToID.end()) continue;
        int tmp = m_wordToID[*j];
        tmpans += m_IDF[tmp] * m_wordInFile[fileID][tmp] * ( 1 + cm_k1 ) / (m_wordInFile[fileID][tmp] + cm_k1 * m_K[fileID]);
    }

    LAC.CutHMM(x, result);
    standardize(result);
    for(auto j = result.begin(); j != result.end(); j++){
        if(m_wordToID.find(*j) == m_wordToID.end()) continue;
        int tmp = m_wordToID[*j];
        tmpans += m_IDF[tmp] * m_wordInFile[fileID][tmp] * ( 1 + cm_k1 ) / (m_wordInFile[fileID][tmp] + cm_k1 * m_K[fileID]);
    }

    return tmpans;
}

void BM25Model::OutputData(std::ostream &fout){
    fout << m_wordToID.size() << std::endl;
    std::cerr << m_wordToID.size() << std::endl;
    for(auto i = m_wordToID.begin();            i != m_wordToID.end(); i++)    fout << i -> first << '\n' << i -> second << std::endl;
    fout << m_existTimes.size() << std::endl;
    std::cerr << m_existTimes.size() << std::endl;
    for(auto i = m_existTimes.begin();          i != m_existTimes.end(); i++)   fout << *i << std::endl;
    fout << m_existTimesInFiles.size() << std::endl;
    std::cerr << m_existTimesInFiles.size() << std::endl;
    for(auto i = m_existTimesInFiles.begin();   i != m_existTimesInFiles.end(); i++) fout << *i << std::endl;
    fout << m_IDF.size() << std::endl;
    std::cerr << m_IDF.size() << std::endl;
    for(auto i = m_IDF.begin();                 i != m_IDF.end(); i++)  fout << *i << std::endl;
    fout << m_fileLength.size() << std::endl;
    std::cerr << m_fileLength.size() << std::endl;
    for(auto i = m_fileLength.begin();          i != m_fileLength.end(); i++)    fout << *i <<std::endl;
    fout << m_K.size() << std::endl;
    std::cerr << m_K.size() << std::endl;
    for(auto i = m_K.begin();                   i != m_K.end(); i++)   fout << *i << std::endl;
    fout << m_wordInFile.size() << std::endl;
    std::cerr << m_wordInFile.size() << std::endl;
    for(auto i = m_wordInFile.begin();          i != m_wordInFile.end(); i++){
        fout << i -> size() << std::endl;
        for(auto j = i -> begin();              j != i -> end(); j++){
            fout << j -> first << ' ' << j -> second << std::endl;
        }
    }
}

void BM25Model::InputData(std::istream &fin){
    char tmpc;
    int tmpi1, tmpi2, tmpi3, tmpi4;
    double tmpd1, tmpd2, tmpd3;
    std::string tmps1, tmps2, tmps3;
    fin >> tmpi1;
    fin.get(tmpc);
    for(int i = 1; i <= tmpi1; i++){
        getline(fin, tmps1);
        fin >> tmpi2;
        fin.get(tmpc);
        m_wordToID[tmps1] = tmpi2;}
    fin >> tmpi1;
    for(int i = 1; i <= tmpi1; i++){
        fin >> tmpi2;
        m_existTimes.push_back(tmpi2);}
    fin >> tmpi1;
    for(int i = 1; i <= tmpi1; i++){
        fin >> tmpi2;
        m_existTimesInFiles.push_back(tmpi2);}
    fin >> tmpi1;
    for(int i = 1; i <= tmpi1; i++){
        fin >> tmpd1;
        m_IDF.push_back(tmpd1);}
    fin >> tmpi1;
    for(int i = 1; i <= tmpi1; i++){
        fin >> tmpi2;
        m_fileLength.push_back(tmpi2);}
    fin >> tmpi1;
    for(int i = 1; i <= tmpi1; i++){
        fin >> tmpd1;
        m_K.push_back(tmpd1);}
    fin >> tmpi1;
    for(int i = 1; i <= tmpi1; i++){
        std::map<int,int> tmpmii;
        fin >> tmpi2;    
        for(int j = 1; j <= tmpi2; j++){
            fin >> tmpi3 >> tmpi4;
            tmpmii[tmpi3] = tmpi4;
        }m_wordInFile.push_back(tmpmii);
    }
}

/*
        std::map<std::string, int> m_wordToID;
        std::vector<int> m_existTimes;
        std::vector<int> m_existTimesInFiles;
        std::vector<double> m_IDF;

        //Focus on files;
        std::vector<int> m_fileLength;
        std::vector<double> m_K;
        std::vector<std::map <int, int>> m_wordInFile;
        int m_fileCounter;
        double m_totalFileLength;
        double   m_avgFileLength;
 */