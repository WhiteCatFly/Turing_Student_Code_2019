#ifndef _COWR_URIHelper

#define _COWR_URIHelper

#include <regex>
#include <string>
#include <tuple>

#include <iostream>

#include "Exceptions.hpp"

struct URIInfo {
    std::string scheme;
    std::string auth;
    std::string host;
    std::string port;
    std::string path;
    std::string query;
    std::string fragment;

    static std::tuple<URIInfo, Error> parseString(std::string uri)
    {
        URIInfo ret;
        std::regex uri_regex { "([^:]*):(//[^/]*|)(.*)" };

        std::smatch uri_match;
        if (std::regex_search(uri, uri_match, uri_regex)) {
            ret.scheme = uri_match[1];

            std::string auth = uri_match[2];
            std::string location = uri_match[3];

            std::regex auth_regex { "//([^@]+@|)([^:]+)(:.*|)" };

            if (auth.size()) {
                if (std::regex_search(auth, uri_match, auth_regex)) {
                    ret.auth = uri_match[1];
                    if (ret.auth.size() > 0) {
                        ret.auth = ret.auth.substr(0, ret.auth.size() - 1);
                    }
                    ret.host = uri_match[2].str();
                    ret.port = uri_match[3].str();

                    if (ret.port.size())
                        ret.port = ret.port.substr(1);
                } else
                    return { ret, 1 };
            }

            std::regex location_regex { "([^\\?#]*)(\\?[^#]+|)(#.*|)" };
            if (std::regex_search(location, uri_match, location_regex)) {
                ret.path = uri_match[1].str();

                ret.query = uri_match[2].str();
                if (ret.query.size())
                    ret.query = ret.query.substr(1);

                ret.fragment = uri_match[3].str();
                if (ret.fragment.size())
                    ret.fragment = ret.fragment.substr(1);
            } else
                return { ret, 1 };

            return { ret, 0 };

        } else
            return { ret, 1 };
    }
};

#endif
