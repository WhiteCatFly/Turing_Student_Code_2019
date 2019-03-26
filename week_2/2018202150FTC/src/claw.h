#include <regex>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <string.h>
const std::string root = "info.ruc.edu.cn";

std::string get_content(const std::string & current);

void parse(std::string & content, std::string & current,std::set<std::string> & urls);