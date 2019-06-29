#include <string>
#include "field.h"

friend bool operator < (Field x, Field y){
    return x.m_name < y.m_name;
}

std::string Field::AccessName(){
    return m_name;
}