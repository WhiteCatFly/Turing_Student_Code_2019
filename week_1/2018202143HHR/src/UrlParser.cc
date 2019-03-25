#include <cassert>
#include <cctype>
#include <regex>
#include <iostream>

#include "UrlParser.h"

static void stringToLower(std::string &str) {
    for (size_t i = 0; i < str.length(); i++) str[i] = tolower(str[i]);
}

Url::Url(std::string url) : origin(url) {
    bool isFixed = parseUrl(url);
    assert(isFixed && !protocol.empty() && !host.empty() && isalpha(protocol[0]));
}

Url::Url(std::string url, const Url &referer) : origin(url) {
    bool isFixed = parseUrl(url);

    if (protocol.empty() || host.empty() || !isalpha(protocol[0])) {
        protocol = referer.protocol;
        host = referer.host;
    }

    if (!isFixed) {
        size_t pos = referer.path.rfind('/');
        assert(pos != std::string::npos);
        path = referer.path.substr(0, pos + 1) + path;
    }
}

std::string Url::toRequestUrl() const {
    return protocol + host + path + query;
}

bool Url::parseUrl(std::string &url) {
    // + protocol://do.ma.in:port/lo/ca/ti/on?
    // + protocol:do.ma.in:port/lo/ca/ti/on?
    // + protocol:i@do.ma.in
    // + //do.ma.in:port/lo/ca/ti/on?
    // + /lo/ca/ti/on?
    // - lo/ca/ti/on?
    std::regex re("^(?:((?:[a-zA-Z0-9]+:)?//)([a-zA-Z0-9\\.\\-@]+(?::\\d+)?))?((?:/.*)?)$");
    std::smatch match;

    std::string location;
    bool isFixed;
    if (std::regex_search(url, match, re)) {
        protocol = match[1];
        stringToLower(protocol);

        host = match[2];
        stringToLower(host);

        location = match[3];
        if (location.empty()) location = '/';
        isFixed = true;
    } else {
        location = std::move(url);
        isFixed = false;
    }

    parseLocation(location);
    return isFixed;
}

void Url::parseLocation(std::string location) {
    size_t pos;

    if ((pos = location.find('#')) != std::string::npos) {
        hash = location.substr(pos);
        location = location.substr(0, pos);
    }

    if ((pos = location.find('?')) != std::string::npos) {
        query = location.substr(pos);
        location = location.substr(0, pos);
    }

    path = std::move(location);
}
