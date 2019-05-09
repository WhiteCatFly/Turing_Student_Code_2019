#ifndef _MENCI_WEB_CRAWLER_REQUESTOPTIONS_H
#define _MENCI_WEB_CRAWLER_REQUESTOPTIONS_H

#include "StringEx.h"

struct RequestOptions {
    size_t maxConcurrenteCount;
    StringEx wgetCommand;
    size_t wgetTimeout;
    size_t wgetWaitRetry;
    size_t wgetTries;
};

#endif // _MENCI_WEB_CRAWLER_REQUESTOPTIONS_H
