#include <string>
#include "document.h"
#include "field.h"

void Document::AddField(Field x){
    m_element.insert(x);
}

Field Document::SearchField(std::string name){
    Field tmp = Field(name);
    return * (m_element.find(tmp));
}