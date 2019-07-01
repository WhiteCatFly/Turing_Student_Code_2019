#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "field.h"
//#include "stringfield.h"
//#include "numberfield.h"
//#include "datefield.h"
#include "searchengine.h"
#include "document.h"
#include "valuation.h"

void Loaddata(std::vector <Document> &library){
    std::ifstream fin;
    fin.open("data.txt");
    while(!fin.eof()){
        std::string tmpstr;
        int tmpnum, tmpnum1, tmpnum2, tmpnum3;
        library.push_back(Document());
        int id = library.size() - 1;
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("name",   tmpstr) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("gender", tmpstr) );
        fin >> tmpnum;  library[id].AddField( (Field *) new NumberField ("age",    tmpnum) );
        fin >> tmpnum;  library[id].AddField( (Field *) new NumberField ("height", tmpnum) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("birthplace", tmpstr) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("lostplace" , tmpstr) );
        fin >> tmpnum1 >> tmpnum2 >> tmpnum3;
        library[id].AddField( (Field *) new DateField ("lostdate", tmpnum1, tmpnum2, tmpnum3) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("others", tmpstr));
    }
}

void SearchEngine::Initialize(){
    Loaddata(m_library);
}

void Analyze(std::vector <Field *> &lost, std::string information[8]){
    std::stringstream strin;
    int tmpnum1, tmpnum2, tmpnum3;
    lost.push_back( (Field *) new StringField("name",     information[0]) );            //std::cerr << ((StringField *)lost[0]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("gender",   information[1]) );            //std::cerr << ((StringField *)lost[1]) -> AccessVal() << std::endl;
    strin = (std::stringstream)(information[2]);
    strin >> tmpnum1;
    lost.push_back( (Field *) new NumberField("age",      tmpnum1) );                   //std::cerr << ((NumberField *)lost[2]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("birthplace",   information[3]));         //std::cerr << ((StringField *)lost[3]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("lostplace",    information[4]));         //std::cerr << ((StringField *)lost[4]) -> AccessVal() << std::endl;
    strin = (std::stringstream)(information[5]);
    strin >> tmpnum1 >> tmpnum2 >> tmpnum3;
    lost.push_back( (Field *) new DateField  ("lostdate", tmpnum1, tmpnum2, tmpnum3));  //std::cerr << ((StringField *)lost[5]) -> AccessVal() << std::endl;
    strin = (std::stringstream)(information[6]);
    strin >> tmpnum1;
    lost.push_back( (Field *) new NumberField("height",   tmpnum1));                    //std::cerr << ((NumberField *)lost[6]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("others",   information[7]));             //std::cerr << ((StringField *)lost[7]) -> AccessVal() << std::endl;
}

bool cmp(Document *x, Document *y){
    return x -> AccessVal() > y -> AccessVal();
}

std::string SearchEngine::Search(std::string information[8]/*std::vector <Field> lost*/){
    std::vector <Field *> lost;
    Analyze(lost, information);
    for(int i = 0; i < m_library.size(); i++) 
        m_library[i].ClearVal();
    for(int i = 0; i < lost.size(); i++){
        Field * currentLost = lost[i];
        std::string fieldName = currentLost -> AccessName();
        for(int j = 0; j < m_library.size(); j++){
            
            Field * currentFound = m_library[j].SearchField( fieldName );
            std::cerr << currentFound -> AccessName() << ' ';
            if(fieldName == "name") m_library[j].AddVal( MatchName  ( (StringField *) currentLost , (StringField *) currentFound ) );
            if(fieldName =="gender")m_library[j].AddVal( MatchGender( (StringField *) currentLost , (StringField *) currentFound ) );
            if(fieldName == "age")  m_library[j].AddVal( MatchAge   ( (NumberField *) currentLost , (NumberField *) currentFound ) );
            if(fieldName =="height")m_library[j].AddVal( MatchHeight( (NumberField *) currentLost , (NumberField *) currentFound ) );
            //if(fieldName =="others")m_library[i].AddVal( MatchOthers( (StringField *) currentLost , (StringField *) currentFound ) );
            if(fieldName =="lostdate")   m_library[j].AddVal( MatchLostDate   ( (DateField   *) currentLost, (DateField   *) currentFound) );
            if(fieldName =="birthplace") m_library[j].AddVal( MatchBirthPlace ( (StringField *) currentLost, (StringField *) currentFound) );
            if(fieldName == "lostplace") m_library[j].AddVal( MatchLostPlace  ( (StringField *) currentLost, (StringField *) currentFound) );
            std::cerr << m_library[j].AccessVal() << std::endl;
        }
    }

    std::cerr << "StageFinished" << std::endl;

    std::vector <Document *> finalAnswer;
    for(int i = 0; i < m_library.size(); i++)
        finalAnswer.push_back(&m_library[i]);
    std::sort(finalAnswer.begin(), finalAnswer.end(), cmp);

    for(int i = 0; i < finalAnswer.size(); i++){
        Field * currentFound = finalAnswer[i] -> SearchField( "name" );
        StringField * tmp = (StringField *) currentFound;
        std::cerr << tmp -> AccessVal() << std::endl;
        return tmp -> AccessVal();
    }
}

