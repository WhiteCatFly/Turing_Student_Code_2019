#ifndef __STATISTICS_H__
#define __STATISTICS_H__

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include<regex>
#include<unistd.h>

#include"Person.h"
#include"Date.h"

int string_to_int(const std::string &str);
void string_replace(std::string &str, const std::string &strold, const std::string &strnew);
Date string_to_date(const std::string &string_date);

    class Statistics
{
    friend class Base;

  private:
    std::vector<int> positions;
    int maximum;
    std::string Content;
  public:
    //Statistics() : maximum(2000) {}
    ~Statistics() {}
    Statistics();
};

#endif