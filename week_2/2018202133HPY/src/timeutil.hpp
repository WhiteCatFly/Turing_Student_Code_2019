#ifndef _COWR_TIME
#define _COWR_TIME

#include <sys/time.h>
#include <unistd.h>

using millisecond_t = long long;

millisecond_t getNowTime();

#endif
