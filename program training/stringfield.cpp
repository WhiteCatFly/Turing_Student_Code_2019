#include <string>
#include "stringfield.h"

bool StringField::contain(std::string x){
    int i = 0, j = 0;
    while(i < m_val.size() && j < x.size()){
        if(m_val[i] == x[j]) i++, j++;
        else i++;
    }if(j == x.size()) return true;
    else return false;
}