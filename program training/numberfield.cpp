#include "numberfield.h"
#include <cmath>
//height weight(nope) age
bool NumberField::AccurateSearch(double x, double range = 0.01){
    if(fabs(x - m_val) <= range) return true;
    return false;
}
