#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__

#include<vector>

#include"Base.h"


class Base;
class QueryResult
{
  private:
    int max_result;
    std::vector<int> result;

  public:
    // friend class Base;
    QueryResult() { max_result = 10; };
    QueryResult(std::vector<int> result_)
    {
        result = result_;
        max_result = 10;
    }
    QueryResult(const QueryResult&other) {max_result = other.max_result; result = other.result;}
    QueryResult(std::vector<int> result_, int limitation)
    {
        max_result = limitation;
        result = result_;
    }
    void set_result(std::vector<int> result_) { result = result_; }
    void show(Base &base);
    int operator[](int a) { return result[a]; }
    ~QueryResult(){};
    int size() {return result.size();}
};

#endif