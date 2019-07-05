#ifndef __SCORE_H__
#define __SCORE_H__

#include <map>
#include <vector>

#include "QueryResult.h"

class QueryResult;

class Score{
friend class Base;
private:
    std::map<int, double> people_score;
public:
    void add_score(int, double);
    QueryResult rank();
};

#endif