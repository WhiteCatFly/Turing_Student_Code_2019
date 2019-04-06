#ifndef _MENCI_WEB_CRAWLER_ARGUMENTS_H
#define _MENCI_WEB_CRAWLER_ARGUMENTS_H

#include "StringEx.h"
#include "RequestOptions.h"

struct Arguments {
    StringEx rootUrl;
    StringEx outputDirectory;
    StringEx suffixBlackList;
    StringEx crawlingRegex;
    StringEx indexSaveFilename;
    RequestOptions requestOptions;
};

Arguments parseArguments(int argc, char *argv[]);

#endif // _MENCI_WEB_CRAWLER_ARGUMENTS_H
