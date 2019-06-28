#include "numberfield.h"
#include <cmath>

bool NumberField::AccurateSearch(double x, double range = sm_eps){
    if(fabs(x - m_val) <= range) return true;
    return false;
}
