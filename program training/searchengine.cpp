#include "searchengine.h"
#include "document.h"
#include "valuation.h"

void Loaddata(vector <Document> &library){
    
}

void SearchEngine::Initialize(){
    Loaddata(m_library);
}

vector <Document> & SearchEngine::search(vector <Field> lost){
    for(int i = 0; i < m_element.size(); i++) 
        m_element[i].ClearVal();
    for(int i = 0; i < lost.size(); i++){
        Field currentLost = lost[i];
        std::string fieldName = currentLost.AccessName();
        for(int j = 0; j < m_element.size(); j++){
            Field currentFound = m_element[j].SearchField( fieldName );
            if(fieldName == "name") m_element[i].AddVal( MatchName  ( (StringField *) &currentLost , (StringField *) &currentFound ) );
            if(fieldName == "sex")  m_element[i].AddVal( MatchSex   ( (StringField *) &currentLost , (StringField *) &currentFound ) );
            if(fieldName == "age")  m_element[i].AddVal( MatchAge   ( (NumberField *) &currentLost , (NumberField *) &currentFound ) );
            if(fieldName =="height")m_element[i].Addval( MatchHeight( (NumberField *) &currentLost , (NumberField *) &currentFound ) );
            if(fieldName =="others")m_element[i].Addval( MatchOthers( (StringField *) &currentLost , (StringField *) &currentFound ) );
            if(fieldName =="birthplace") m_element[i].Addval( MatchBirthPlace ( (StringField *) &currentLost, (StringField *) &currentFound) );
            if(fieldName == "lostplace") m_element[i].Addval( MatchLostPlace  ( (StringField *) &currentLost, (StringField *) &currentFound) );
        }
    }

}

