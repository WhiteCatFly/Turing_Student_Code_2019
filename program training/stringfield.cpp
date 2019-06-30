#include <string>
#include "stringfield.h"

//name sex birthPlace lostPlace

std::string StringField::AccessVal(){
    return m_val;
}

bool StringField::Contain(std::string x){
    int i = 0, j = 0;
    while(i < m_val.size() && j < x.size()){
        if(m_val[i] == x[j]) i++, j++;
        else i++;
    }
    if(j == x.size()) return true;
    i = 0, j = 0;
    while(i < m_val.size() && j < x.size()){
        if(m_val[i] == x[j]) i++, j++;
        else j++;
    }
    if(i == m_val.size()) return true;
    return false;
}

bool StringField::Contain(StringField x){
    return this -> Contain(x.AccessVal());
}

bool StringField::Equal(std::string x){
    return x == m_val;
}

bool StringField::Equal(StringField x){
    return this -> Equal(x.AccessVal());
}

int StringField::Levenshtein(std::string x){

}