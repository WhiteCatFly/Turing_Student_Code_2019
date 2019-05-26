#ifndef __BUILDINDEX_H__
#define __BUILDINDEX_H__

#include<iostream>
#include<string>
#include<set>
#include<map>
#include<algorithm>
#include<vector>
#include<fstream>
#include<cmath>

struct Sites
{
  std::string url;
  double tf;
  bool set_or_not;
  // double idf;
  double tf_idf;
  Sites(std::string str)
  {
    url = str;
    tf = 0;
    // idf = 0;
    tf_idf = 0;
    set_or_not = false;
  }
};


class BuildIndex{
private:
  std::map<std::string, std::vector<Sites>> SearchTable;

  std::map<std::string, std::set<std::string>> SearchTable_No_;

  int the_number_of_sites;
public:
  void Add(const std::string &url);
  BuildIndex(){};
  ~BuildIndex(){};
  void Answer(const std::string &query);
  void GetIdf();
  void Rank();
};























#endif