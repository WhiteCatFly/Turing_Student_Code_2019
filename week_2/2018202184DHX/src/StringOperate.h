#ifndef STRINGOPERATE_H_INCLUDED
#define STRINGOPERATE_H_INCLUDED

#include <string>
#include "bfs.h"
const std::string Title = "info.ruc.edu.cn";
const int MAX = 20;
const char BlackList[][MAX] = {".doc" , ".pdf" , ".xls" , "@" , ".css" , "/en/"};
bool BlackListCheck(std::string url);
bool JudgeReOrAb(std::string url);
void RelativeSite(std::string url);
void AbsoluteSite(std::string url);

#endif
