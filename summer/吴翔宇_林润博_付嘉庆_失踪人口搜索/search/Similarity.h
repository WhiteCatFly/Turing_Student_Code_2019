#include <algorithm>
#include <string>
#include <assert.h>
#include "PersonData.h"
using namespace std;

double NameSimilarity(const string p, const string q);

double SexSimilarity(const string p, const string q);

double DaySimilarity(const int p, const int q);

double HeightSimilarity(const int p, const int q);

double PairStringSimilarity(const string p, const pair<string, string> q);

double PairStringSimilarity(const pair<string, string> p, const pair<string, string> q);

double InformationSimilarity(const string p, const string q);