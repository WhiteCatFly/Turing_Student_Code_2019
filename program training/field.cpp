#include <string>
#include "field.h"

std::string Field::AccessName(){
    return m_name;
}

bool operator < (Field x, Field y){
    return x.AccessName() < y.AccessName();
}
