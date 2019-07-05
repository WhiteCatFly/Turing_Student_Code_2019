#ifndef BM25_VALUATOR_H_INCLUDED
#define BM25_VALUATOR_H_INCLUDED

#include "document.h"
#include "field.h" 
#include <map>
#include <vector>

class BM25Model{
    private:
        const double cm_b = 0.75;
        const double cm_k1 = 1.2;
        
        //Focus on words
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
    public:
        BM25Model(){m_fileCounter = 0, m_totalFileLength = 0, m_avgFileLength = 0;}
        ~BM25Model(){}
        std::string AccessName();
        void Clear();
        void Train();
        void OutputData(std::ostream &x);
        void InputData(std::istream &x);
        void AddSource(int fileID, std::string x); 
        double Calculate(int fileID, std::string x);
};

#endif

