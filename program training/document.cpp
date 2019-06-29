#include <string>
#include "document.h"
#include "field.h"

void Document::AddField(Field x){
    x.m_element.insert(x);
}

Field SearchField(std::string name){
    Field tmp = Field(name);
    return * ((this -> element).find(name));
}