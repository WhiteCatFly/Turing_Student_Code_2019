#ifndef NUMBERFIELD_H_INCLUDED
#define NUMBERFIELD_H_INCLUDED

#include "field.h"

class NumberField : public Field{
    private:
        static double sm_eps = 0.01;
        double m_val;
    public:
        NumberField(){}
        NumberField(std::string name, double val) Field(name), m_val(val);
        ~NumberField(){}
        bool AccurateSearch(double x, double range = sm_eps);
};

#endif