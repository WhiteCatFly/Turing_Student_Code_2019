#ifndef VALUATION_H_INCLUDED
#define VALUATION_H_INCLUDED

#include "stringfield.h"
#include "numberfield.h"
#include "datefield.h"

double MatchName    (StringField *x, StringField *y);
double MatchGender  (StringField *x, StringField *y);
double MatchOthers  (StringField *x, StringField *y);
double MatchLostDate(DateField   *x, DateField   *y);
double MatchAge     (NumberField *x, NumberField *y);
double MatchHeight  (NumberField *x, NumberField *y);
double MatchBirthPlace  (StringField *x, StringField *y);
double MatchLostPlace   (StringField *x, StringField *y);

#endif