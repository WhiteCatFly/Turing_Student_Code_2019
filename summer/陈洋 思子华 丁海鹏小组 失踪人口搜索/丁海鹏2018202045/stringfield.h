#ifndef STRINGFIELD_H_INCLUDED
#define STRINGFIELD_H_INCLUDED

#include <string>
#include "field.h"

class StringField : public Field{
    private:
        std::string m_val;
    public:
        StringField(){}
        StringField(std::string name, std::string val): Field(name), m_val(val) {}
        ~StringField(){}
        std::string AccessVal();
        bool Contain    (std::string x);
        bool Contain    (StringField x);
        bool Equal      (std::string x);
        bool Equal      (StringField x);
//        bool match      (std::string x);
};

#endif