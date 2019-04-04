#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>
#include <algorithm>

bool htmlParse(std::string htmlname, std::vector<std::string>& single_url_set, std::vector<std::string>& history_url_set);
//return single_url_set and history_url_set
