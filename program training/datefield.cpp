#include "datefield.h"

double MatchDate(DateField x, DateField y){
    if(x.m_year != y.m_year) return 0;
    if(x.m_month != y.m_month) return 1;
    if(x.m_day != y.m_day) return 2;
    return 3;
}