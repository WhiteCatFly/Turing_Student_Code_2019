#ifndef __QUERY_H__
#define __QUERY_H__

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"

class Query
{
    friend class Base;

  private:
    std::string id;
    std::string name;
    int gender; // 0 for female, 1 for male;
    std::string birthplace;
    std::string birthday;
    int birthyear;
    std::string lostday;
    int lostyear;
    int min_height;
    int max_height;
    std::string lostplace;
    std::string query_string;
    std::vector<bool> descriptions;

    unsigned char ToHex(unsigned char);
    unsigned char FromHex(unsigned char);
    std::string UrlEncode(const std::string&);
    std::string UrlDecode(const std::string& );
  public:
    Query(){};
    Query(const std::string &id_ = "",
          const std::string &name_ = "",
          int gender_ = -1,
          const std::string &birthplace_ = "",
          const std::string &birthday_ = "",
          int birthyear_ = -1,
          const std::string &lostday_ = "",
          int lostyear_ = -1,
          int min_height_ = -1,
          int max_height_ = -1,
          const std::string &lostplace_ = "",
          const std::vector<bool> &descriptions_ = {},
          const std::string &query_string_ = "");
    Query(std::string a, int n);

    std::string GetName(){return name;}
};

#endif