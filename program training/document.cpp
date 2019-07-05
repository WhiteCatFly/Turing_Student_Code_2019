#include <string>
#include "document.h"
#include "field.h"

void Document::AddField(Field * x){
    m_element.push_back(x);
}

Field * Document::SearchField(std::string name){
    Field tmp = Field(name);
    for(int i = 0; i < m_element.size(); i++){
        if(m_element[i] -> AccessName() == name) return m_element[i];
    }
}

void Document::AddVal(double x){
    m_val += x;
}

double Document::AccessVal(){
    return m_val;
}

void Document::ClearVal(){
    m_val = 0;
}

void Document::EditID(std::string x){
    m_ID = x;
}

std::string Document::AccessID(){
    return m_ID;
}