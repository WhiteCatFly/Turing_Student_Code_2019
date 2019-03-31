#include <cctype>
#include <regex>
#include <iostream>

#include "Url.h"

Url::Url(StringEx url) : origin(url) {
    const bool isFixed = parseUrl(url);
    if (!(isFixed && !protocol.empty() && !host.empty() && isalpha(protocol[0]))) {
        std::cout << url << std::endl;
        throw std::logic_error("Invalid url: " + url);
    }

    normalize();
}

Url::Url(StringEx url, const Url &referer) : origin(url) {
    const bool isFixed = parseUrl(url);

    if (protocol.empty() || host.empty() || !isalpha(protocol[0])) {
        protocol = referer.protocol;
        host = referer.host;
    }

    if (!isFixed) {
        const size_t pos = referer.path.reverseFind('/');
        if (pos == StringEx::npos) {
            throw std::logic_error("Invalid url: " + url + ", from " + referer.toString());
        }
        path = referer.path.substr(0, pos + 1) + path;
    }

    normalize();
}

StringEx Url::toString(bool noHostAndProtocol) const {
    if (noHostAndProtocol) {
        return path + query;
    } else {
        return protocol + host + path + query;
    }
}

bool Url::parseUrl(StringEx url) {
    // + protocol://do.ma.in:port/lo/ca/ti/on?
    // + protocol:do.ma.in:port/lo/ca/ti/on?
    // + protocol:i@do.ma.in
    // + //do.ma.in:port/lo/ca/ti/on?
    // + /lo/ca/ti/on?
    // - lo/ca/ti/on?
    static const std::regex re("^(?:((?:[a-zA-Z0-9_]+:)?//)([a-zA-Z0-9\\.\\-@]+(?::\\d+)?))?((?:/.*)?)$");
    std::smatch match;

    StringEx location;
    bool isFixed;
    if (std::regex_search((std::string &)url, match, re)) {
        protocol = match[1];
        protocol = protocol.toLower();

        host = match[2];
        host = host.toLower();

        location = match[3];
        if (location.empty()) location = '/';
        isFixed = true;
    } else {
        location = url;
        isFixed = false;
    }

    parseLocation(location);
    return isFixed;
}

void Url::parseLocation(StringEx location) {
    size_t pos;

    if ((pos = location.find('#')) != StringEx::npos) {
        hash = location.substr(pos);
        location = location.substr(0, pos);
    }

    if ((pos = location.find('?')) != StringEx::npos) {
        query = location.substr(pos);
        location = location.substr(0, pos);
    }

    path = location;
}

void Url::normalize() {
    std::vector<StringEx> array = path.split("/");
    for (std::vector<StringEx>::iterator it = array.begin(); it != array.end(); ) {
        if (*it == ".") it = array.erase(it);
        else if (*it == "..") {
            if (it != array.begin() + 1) { // First element here IS '' before '/'.
                it = array.erase(--it);
            }
            it = array.erase(it);
        } else it++;
    }

    path = StringEx("/").join(array.begin(), array.end());
}
