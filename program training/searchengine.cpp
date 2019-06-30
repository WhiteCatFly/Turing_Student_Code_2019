#include <vector>
#include "field.h"
//#include "stringfield.h"
//#include "numberfield.h"
//#include "datefield.h"
#include "searchengine.h"
#include "document.h"
#include "valuation.h"

void Loaddata(std::vector <Document> &library){
    
}

void SearchEngine::Initialize(){
    Loaddata(m_library);
}

std::vector <Document> SearchEngine::Search(std::vector <Field> lost){
    for(int i = 0; i < m_library.size(); i++) 
        m_library[i].ClearVal();
    for(int i = 0; i < lost.size(); i++){
        Field currentLost = lost[i];
        std::string fieldName = currentLost.AccessName();
        for(int j = 0; j < m_library.size(); j++){
            Field currentFound = m_library[j].SearchField( fieldName );
            if(fieldName == "name") m_library[i].AddVal( MatchName  ( (StringField *) &currentLost , (StringField *) &currentFound ) );
            if(fieldName == "sex")  m_library[i].AddVal( MatchGender( (StringField *) &currentLost , (StringField *) &currentFound ) );
            if(fieldName == "age")  m_library[i].AddVal( MatchAge   ( (NumberField *) &currentLost , (NumberField *) &currentFound ) );
            if(fieldName =="height")m_library[i].AddVal( MatchHeight( (NumberField *) &currentLost , (NumberField *) &currentFound ) );
            if(fieldName =="others")m_library[i].AddVal( MatchOthers( (StringField *) &currentLost , (StringField *) &currentFound ) );
            if(fieldName =="lostdate")   m_library[i].AddVal( MatchLostDate   ( (DateField   *) &currentLost, (DateField   *) &currentFound) );
            if(fieldName =="birthplace") m_library[i].AddVal( MatchBirthPlace ( (StringField *) &currentLost, (StringField *) &currentFound) );
            if(fieldName == "lostplace") m_library[i].AddVal( MatchLostPlace  ( (StringField *) &currentLost, (StringField *) &currentFound) );
        }
    }
}

