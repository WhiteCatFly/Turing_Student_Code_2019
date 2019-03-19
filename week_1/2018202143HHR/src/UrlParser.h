#ifndef _MENCI_WEB_CRAWLER_URLPARSER_H
#define _MENCI_WEB_CRAWLER_URLPARSER_H

#include <string>

class Url {
public:
    std::string protocol;
    std::string host; // hostname:port

    std::string path;
    std::string query;
    std::string hash;

    std::string origin;

    Url(std::string url);
    Url(std::string url, const Url &referer);

    std::string toRequestUrl() const;
private:
    bool parseUrl(std::string &url);
    void parseLocation(std::string location);
};

#endif // _MENCI_WEB_CRAWLER_URLPARSER_H
