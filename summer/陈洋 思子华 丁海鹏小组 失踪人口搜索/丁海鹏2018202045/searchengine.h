#ifndef SEARCHENGINE_H_INCLUDED
#define SEARCHENGINE_H_INCLUDED

#include <string>
#include "stringfield.h"
#include "numberfield.h"
#include "datefield.h"
#include "document.h"
#include "field.h"
#include "BM25_valuator.h"

class SearchEngine{
    private:
        std::vector <Document> m_library;
        std::map <std::string, BM25Model> m_valuator;
    public:
        SearchEngine(){}
        ~SearchEngine(){}
        void Initialize();
        void Initialize2();
        std::vector< std::vector <std::string> > Search (std::string information[8]);//Interface is waiting for deciding.

        double MatchName    (StringField *x, StringField *y);
        double MatchGender  (StringField *x, StringField *y);
        double MatchOthers  (StringField *x, int fileID);
        double MatchLostDate(DateField   *x, DateField   *y);
        double MatchAge     (NumberField *x, NumberField *y);
        double MatchHeight  (NumberField *x, NumberField *y);
        double MatchBirthPlace  (StringField *x, int fileID);
        double MatchLostPlace   (StringField *x, int fileID);
};

#endif