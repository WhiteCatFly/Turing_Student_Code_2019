#define FULLY_EQUALED 1.0
#define CONTAINED 0.8
#include "stringfield.h"
#include "datefield.h"
#include "numberfield.h"
#include "valuation.h"

double MatchName (StringField *x, StringField *y){
    if( x -> Equal  ( *y ) ) return FULLY_EQUALED;
    if( x -> Contain( *y ) ) return CONTAINED;
}

double MatchGender (StringField *x, StringField *y){
    if( x -> Equal( *y ) ) return FULLY_EQUALED;
}

double MatchLostDate(DateField *x, DateField *y){
    
}

double 