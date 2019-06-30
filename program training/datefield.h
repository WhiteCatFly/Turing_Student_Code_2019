#ifndef DATEFIELD_H_INCLUDED
#define DATEFIELD_H_INCLUDED

#include <string>
#include "field.h"

class DateField : public Field{
    private:
        int m_year, m_month, m_day;        
    public:
        DateField(){}
        DateField(std::string name, int year = 0, int month = 0, int day = 0):
            Field(name), m_year(year), m_month(month), m_day(day)
        {}
        ~DateField(){}
    friend int MatchDate(Date x, Date y);
};

#endif