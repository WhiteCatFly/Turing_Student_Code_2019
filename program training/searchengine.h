#ifndef SEARCHENGINE_H_INCLUDED
#define SEARCHENGINE_H_INCLUDED

#include <string>
#include "document.h"
//#include <field.h>

class SearchEngine{
    private:
        vector <Document> m_library;
    public:
        SearchEngine(){}
        ~SearchEngine(){}
        void Initialize();
        Search();//Interface is waiting for deciding.
}

#endif