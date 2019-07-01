#ifndef SEARCHENGINE_H_INCLUDED
#define SEARCHENGINE_H_INCLUDED

#include <string>
#include "document.h"
#include "field.h"

class SearchEngine{
    private:
        std::vector <Document> m_library;
    public:
        SearchEngine(){}
        ~SearchEngine(){}
        void Initialize();
        std::string Search (std::string information[8]);//Interface is waiting for deciding.
};

#endif