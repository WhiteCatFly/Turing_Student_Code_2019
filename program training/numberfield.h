#ifndef NUMBERFIELD_H_INCLUDED
#define NUMBERFIELD_H_INCLUDED

#include <string>
#include "field.h"

class NumberField : public Field{
    private:
        const double c_eps = 0.01;
        double m_val;
    public:
        NumberField(){}
        NumberField(std::string name, double val) : Field(name), m_val(val) {}
        ~NumberField(){}
        double AccessVal();
        bool AccuratCompare(double x, double range = 0.01);
};

#endif