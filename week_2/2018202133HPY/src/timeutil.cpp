#include "timeutil.hpp"

millisecond_t getNowTime()
{
    struct timeval time;
    gettimeofday(&time, NULL);

    return time.tv_sec * 1000 + time.tv_usec / 1000;
}
