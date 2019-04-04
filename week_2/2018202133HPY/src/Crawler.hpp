#ifndef _CRAWLER

#define _CRAWLER

#include <exception>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "CurlEasyHandle.hpp"

class URLParseError : public std::exception {
public:
    virtual const char* what()
    {
        return "url_parse_error";
    }
};

class ParamTypeError : public std::exception {
public:
    virtual const char* what()
    {
        return "param_type_error";
    }
};

void createParentDirectory(std::string pathstr);
std::string getBasename(std::string pathstr);
std::string getSavePath(std::string url);
std::string getPath(std::string url);
std::string getProto(std::string url);
std::string getSite(std::string url);
std::vector<std::string> findURLs(std::string proto,
    std::string site,
    std::string path,
    std::string data);
void addCurlHandle(std::string url,
    std::function<void(std::vector<char>&, std::map<std::string, std::string>&, CurlEasyHandle&)> dataCallback,
    std::function<void(CurlEasyHandle&)> headerCallback = CurlEasyHandle::curlDefaultHeaderReceiveHandler);
void processURL(std::string url);
#endif
