#ifndef INTERNETWORM_H
#define INTERNETWORM_H

#include <string>
#include <queue>

bool Loader         (std::string url, std::string &page);
void Extracter      (std::string &page, std::queue <std::string> &newurls);
std::string Filter  (std::string currenturl, std::string newurl);

#endif

