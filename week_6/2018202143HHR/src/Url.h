#ifndef _MENCI_WEB_CRAWLER_URL_H
#define _MENCI_WEB_CRAWLER_URL_H

#include "StringEx.h"

class Url {
public:
    StringEx protocol;
    StringEx host; // hostname:port

    StringEx path;
    StringEx query;
    StringEx hash;

    StringEx origin;

    Url() {};
    Url(StringEx url);
    Url(StringEx url, const Url &referer);

    StringEx toString(bool noHostAndProtocol = false) const;
private:
    bool parseUrl(StringEx url);
    void parseLocation(StringEx location);
    void normalize();
};

#endif // _MENCI_WEB_CRAWLER_URL_H
