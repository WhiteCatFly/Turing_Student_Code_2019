#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <string>

class Field{
    private:
        std::string m_name;
    public:
        Field(){}
        Field(std::string x):m_name(x) {}
        ~Field(){}
        std::string AccessName();
};

bool operator < (Field x, Field y);

#endif
