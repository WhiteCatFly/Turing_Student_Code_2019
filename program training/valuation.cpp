#define CONTAINED 0.8
#define FULLY_EQUALED 1.0

#define MATCH_YEAR 0.5
#define MATCH_MONTH 0.8
#define MATCH_DAY 1.0

#define ACCURATE 1.0
#define DEVIATE 0.8

#define DIFFERENT 0.0

#define PLACEFORM(x,y) (0.4 + 0.6 * y / x)

#include "stringfield.h"
#include "datefield.h"
#include "numberfield.h"
#include "valuation.h"

#include <iostream>
#include <sstream>

double MatchName (StringField *x, StringField *y){
    if( x -> Equal( *y ) ) return FULLY_EQUALED * 5;
    else if( x -> Contain( *y ) ) return CONTAINED * 2;
    else return DIFFERENT;
}

double MatchGender (StringField *x, StringField *y){
    if( x -> Equal( *y ) ) return FULLY_EQUALED * 3;
    else return DIFFERENT;
}

double MatchLostDate(DateField *x, DateField *y){
    int tmp = MatchDate(*x, *y);
    if(tmp == 0) return DIFFERENT;
    else if(tmp == 1) return MATCH_YEAR;
    else if(tmp == 2) return MATCH_MONTH;
    else if(tmp == 3) return MATCH_DAY;
}

double MatchHeight(NumberField *x, NumberField *y){
    if( x -> AccurateCompare ( y -> AccessVal() , 0.01) ) return ACCURATE;
    if( x -> AccurateCompare ( y -> AccessVal() , 5.01 ) ) return DEVIATE;
    return DIFFERENT;
}

double MatchAge(NumberField *x, NumberField *y){
    if( x -> AccurateCompare ( y -> AccessVal() , 0.01) ) return ACCURATE;
    if( x -> AccurateCompare ( y -> AccessVal() , 2.01 ) ) return DEVIATE;
    return DIFFERENT;
}

double MatchBirthPlace(StringField *ori_x, StringField *ori_y){
    std::string y = ori_y -> AccessVal();
    std::stringstream ystream(y);
    std::string tmp;
    double matched = 0;
    double total = 0;
    while(!ystream.eof()){
        ystream >> tmp;
        if(ori_x -> Contain(tmp)) matched ++;
        total ++;
    }if(matched == 0) return DIFFERENT;
    return PLACEFORM(total, matched);
}

double MatchLostPlace(StringField *ori_x, StringField *ori_y){
    return MatchBirthPlace(ori_x, ori_y);
}

double MatchOthers(StringField *ori_x, StringField *ori_y){
    
}