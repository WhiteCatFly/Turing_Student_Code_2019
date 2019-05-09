#ifndef _COWR_UTILS_TIMEUTIL
#define _COWR_UTILS_TIMEUTIL

#include <sys/time.h>
#include <unistd.h>

namespace cowr {

using millisecond_t = long long;

millisecond_t getNowTime();

}
#endif
