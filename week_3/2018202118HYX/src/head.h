#ifndef HEAD_H
#define HEAD_H
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <queue>
#include <regex>
#include <set>

void input_first_url(std::string &url);
class crawl
{
private:
  std::queue<std::string> todo;
  std::set<std::string> done;

  int n;
  std::string current;
  std::string root;

  std::string getcontent();
  int adjust(std::string &a_url);
  void parse(std::string &content, std::set<std::string> &urls);
public:
  crawl()=default;
  crawl(std::string root_);
  ~crawl();
  void BFS();
};
#endif
