#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "field.h"
#include "stringfield.h"
#include "numberfield.h"
#include "datefield.h"
#include "searchengine.h"
#include "document.h"
#include "cppjieba/include/cppjieba/Jieba.hpp"

const char* const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";

cppjieba::Jieba LAC(DICT_PATH,  HMM_PATH,   USER_DICT_PATH, IDF_PATH,   STOP_WORD_PATH);
std::set <std::string> stopWords;
std::map <std::string, std::string> synonyms;

double STOF(std::string x){
    return atof(x.c_str());
}

int STOI(std::string x){
    return atoi(x.c_str());
}

void LoadData(std::vector <Document> &library){
    std::ifstream fin;
    fin.open("data_ex.txt");
    while(!fin.eof()){
        std::string tmpstr, tmpstr1, tmpstr2, tmpstr3;
        library.push_back(Document());
        int id = library.size() - 1;
        fin >> tmpstr;  library[id].EditID(tmpstr);
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("name",   tmpstr) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("gender", tmpstr) );
        fin >> tmpstr;  library[id].AddField( (Field *) new NumberField ("age",    STOF(tmpstr) ) );
        fin >> tmpstr;  library[id].AddField( (Field *) new NumberField ("height", STOF(tmpstr) ) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("birthplace", tmpstr) );
        fin >> tmpstr1 >> tmpstr2 >> tmpstr3;
        library[id].AddField( (Field *) new DateField ("lostdate", STOF(tmpstr1), STOF(tmpstr2), STOF(tmpstr3)) );
        fin >> tmpstr;  library[id].AddField( (Field *) new StringField ("lostplace" , tmpstr) );
        getline(fin, tmpstr); library[id].AddField( (Field *) new StringField ("others", tmpstr));
    }
}

void LoadStopWords(){
    std::ifstream fin;
    fin.open("stop_words.txt");
    while(!fin.eof()){
        std::string tmp;
        fin >> tmp;
        stopWords.insert(tmp);
    }
}

void LoadSynonyms(){
    std::ifstream fin;
    fin.open("synonyms.txt");
    while(!fin.eof()){
        std::string header, tmp1, tmp2;
        fin >> tmp1;
        getline(fin, tmp1);
        std::stringstream tmpsin(tmp1);
        tmpsin >> header;
        synonyms[header] = header;
        while(!tmpsin.eof()){
            tmpsin >> tmp2;
            synonyms[tmp2] = header;
        }
    }
}

void SearchEngine::Initialize(){
    LoadData(m_library);
    LoadStopWords();
    LoadSynonyms();
    std::cerr << "Data Loaded" << std::endl;
    for(int i = 0; i < m_library.size(); i++){
        if(i % (m_library.size() / 10) == 1 ) 
            std::cerr << (i - 1) * 10 / m_library.size() + 1 << "0% data calculated" << std::endl; 
        m_valuator["birthplace"].AddSource( i, ( (StringField *) m_library[i].SearchField("birthplace") ) -> AccessVal() );
        m_valuator["lostplace" ].AddSource( i, ( (StringField *) m_library[i].SearchField("lostplace" ) ) -> AccessVal() );
        m_valuator["others"    ].AddSource( i, ( (StringField *) m_library[i].SearchField("others"      ) ) -> AccessVal() );   
    }
    m_valuator["birthplace"].Train();
    m_valuator["lostplace" ].Train();
    m_valuator["others"    ].Train();
    std::cerr << "Initializing complete" << std::endl;
    
    std::ofstream data("data.txt");
    m_valuator["birthplace"].OutputData(data);
    std::cerr << "Initializing complete" << std::endl;
    
    m_valuator["lostplace" ].OutputData(data);
    std::cerr << "Initializing complete" << std::endl;
    
    m_valuator["others"    ].OutputData(data);
    std::cerr << "Initializing complete" << std::endl;
    
}

void SearchEngine::Initialize2(){
    LoadData(m_library);
    LoadStopWords();
    LoadSynonyms();
    std::ifstream data("data.txt");
    m_valuator["birthplace"].InputData(data);
    m_valuator["lostplace" ].InputData(data);
    m_valuator["others"    ].InputData(data);
}

void Analyze(std::vector <Field *> &lost, std::string information[8]){
    std::stringstream strin;
    std::string tmpstr1, tmpstr2, tmpstr3;
    lost.push_back( (Field *) new StringField("name",         information[0]) );        //std::cerr << ((StringField *)lost[0]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("gender",       information[1]) );        //std::cerr << ((StringField *)lost[1]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new NumberField("age",     STOF(information[2])) );       //std::cerr << ((NumberField *)lost[2]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("birthplace",   information[3]));         //std::cerr << ((StringField *)lost[3]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("lostplace",    information[4]));         //std::cerr << ((StringField *)lost[4]) -> AccessVal() << std::endl;
    strin = (std::stringstream)(information[5]);
    strin >> tmpstr1 >> tmpstr2 >> tmpstr3;
    lost.push_back( (Field *) new NumberField("height",   STOF(information[6])));                    //std::cerr << ((NumberField *)lost[6]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new DateField  ("lostdate", STOF(tmpstr1), STOF(tmpstr2), STOF(tmpstr3) ));  //std::cerr << ((StringField *)lost[5]) -> AccessVal() << std::endl;
    lost.push_back( (Field *) new StringField("others",   information[7]));             //std::cerr << ((StringField *)lost[7]) -> AccessVal() << std::endl;
}

bool cmp(Document *x, Document *y){
    return x -> AccessVal() > y -> AccessVal();
}

std::string CheckS(std::string x){
    if(x[0] == '0' || x[0] == '-') return "不详";
    else return x;
}

std::string CheckN(int x){
    std::string res;
    if(x <= 0) return "不详";
    while(x > 0){
        res += '0' + x%10;
        x /= 10;
    }reverse(res.begin(), res.end());
    return res;
}

std::vector< std::vector <std::string> > SearchEngine::Search(std::string information[8]/*std::vector <Field> lost*/){
    std::vector <Field *> lost;
    Analyze(lost, information);
    for(int i = 0; i < m_library.size(); i++) 
        m_library[i].ClearVal();
    for(int i = 0; i < lost.size(); i++){
        Field * currentLost = lost[i];
        std::string fieldName = currentLost -> AccessName();
//        std::cerr << fieldName << std::endl;
        for(int j = 0; j < m_library.size(); j++){
            Field * currentFound = m_library[j].SearchField( fieldName );
            if(fieldName =="name")  m_library[j].AddVal( MatchName  ( (StringField *) currentLost , (StringField *) currentFound ) );
            if(fieldName =="gender")m_library[j].AddVal( MatchGender( (StringField *) currentLost , (StringField *) currentFound ) );
            if(fieldName =="age")   m_library[j].AddVal( MatchAge   ( (NumberField *) currentLost , (NumberField *) currentFound ) );
            if(fieldName =="height")m_library[j].AddVal( MatchHeight( (NumberField *) currentLost , (NumberField *) currentFound ) );
            if(fieldName =="lostdate")   m_library[j].AddVal( MatchLostDate   ( (DateField   *) currentLost, (DateField   *) currentFound) );
            if(fieldName =="birthplace") m_library[j].AddVal( MatchBirthPlace ( (StringField *) currentLost, j ) );
            if(fieldName =="lostplace")  m_library[j].AddVal( MatchLostPlace  ( (StringField *) currentLost, j ) );
            if(fieldName =="others")     m_library[j].AddVal( MatchOthers     ( (StringField *) currentLost, j ) );
        }
    }
    
    std::vector <Document *> finalAnswer;
    
    for(int i = 0; i < m_library.size(); i++)
        finalAnswer.push_back(&m_library[i]);
    std::sort(finalAnswer.begin(), finalAnswer.end(), cmp);
    
    std::vector <std::vector <std::string>> returnPack;
    std::vector <std::string> returnPackPart;
    for(int i = 0; i < 5; i++){
        returnPackPart.clear();
//        std::cerr << finalAnswer[i] -> AccessVal() << std::endl;
        returnPackPart.push_back( "姓名：" + CheckS(( (StringField *) (finalAnswer[i] -> SearchField( "name"   ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "性别：" + CheckS(( (StringField *) (finalAnswer[i] -> SearchField( "gender" ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "年龄：" + CheckN(( (NumberField *) (finalAnswer[i] -> SearchField( "age"    ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "出生地点：" + CheckS(( (StringField *) (finalAnswer[i] -> SearchField( "birthplace" ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "丢失地点：" + CheckS(( (StringField *) (finalAnswer[i] -> SearchField( "lostplace"  ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "丢失日期：" + CheckN(( (DateField   *) (finalAnswer[i] -> SearchField( "lostdate"   ) ) ) -> AccessYear()) );
        returnPackPart.push_back( "身高：" + CheckN(( (NumberField *) (finalAnswer[i] -> SearchField( "height"     ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "其他信息：" + CheckS(( (StringField *) (finalAnswer[i] -> SearchField( "others"     ) ) ) -> AccessVal()) );
        returnPackPart.push_back( "http://www.zgszrkdak.com/show.asp?id=" + finalAnswer[i] -> AccessID());
        returnPack.push_back( returnPackPart );
    }return returnPack;
}

#define CONTAINED 0.8
#define FULLY_EQUALED 1.0

#define MATCH_YEAR 0.5
#define MATCH_MONTH 0.8
#define MATCH_DAY 1.0

#define ACCURATE 1.0
#define DEVIATE 0.8

#define DIFFERENT 0.0

#define PLACEFORM(x,y) (0.4 + 0.6 * y / x)

double SearchEngine::MatchName (StringField *x, StringField *y){
    if(x -> AccessVal() == "") return DIFFERENT;
    else if( x -> Equal( *y ) ) return 4;
    else return DIFFERENT;
}

double SearchEngine::MatchGender (StringField *x, StringField *y){
    if(x -> AccessVal() == "") return DIFFERENT;
    if(x -> Equal( *y ) ) return 10;
    else return DIFFERENT;
}

double SearchEngine::MatchLostDate(DateField *x, DateField *y){
    int tmp = MatchDate(*x, *y);
    if(tmp == 0) return DIFFERENT;
    else if(tmp == 1) return 4;
    else if(tmp == 2) return MATCH_MONTH;
    else if(tmp == 3) return MATCH_DAY;
}

double SearchEngine::MatchHeight(NumberField *x, NumberField *y){
    if( x -> AccurateCompare ( y -> AccessVal() , 0.01) ) return 3;
    if( x -> AccurateCompare ( y -> AccessVal() , 5.01) ) return 1;
    return DIFFERENT;
}

double SearchEngine::MatchAge(NumberField *x, NumberField *y){
    if( x -> AccurateCompare ( y -> AccessVal() , 0.01) ) return 3;
    if( x -> AccurateCompare ( y -> AccessVal() , 2.01) ) return 1;
    return DIFFERENT;
}


double SearchEngine::MatchBirthPlace(StringField *ori_x, int fileID){
    return 0.5 * m_valuator["birthplace"].Calculate(fileID, ori_x -> AccessVal());
}

double SearchEngine::MatchLostPlace(StringField *ori_x, int fileID){
    return 0.5 * m_valuator["lostplace"].Calculate(fileID, ori_x -> AccessVal());
}

double SearchEngine::MatchOthers(StringField *ori_x, int fileID){
    return m_valuator["others"].Calculate(fileID, ori_x -> AccessVal());
}
