#include "CurlEasyHandle.hpp"

#include <mutex>
#include <sstream>
#include <string>

namespace cowr {
size_t CurlEasyHandle::curlHeaderHandleFunc(void* buffer, size_t size, size_t nmemb, void* userp)
{
    auto that = (CurlEasyHandle*)userp;

    std::lock_guard lock_that { that->lock };

    std::string key, val;
    std::stringstream ss;

    ss.write((const char*)buffer, nmemb);

    if (!(ss >> key)) {
        that->on_header_receive(*that);
    } else if (key.substr(0, 4) == "HTTP") {
        that->env["HTTP_VER"] = key.substr(5);

        ss >> val;

        that->env["STATUS_CODE"] = val;

        getline(ss, val);
        val.erase(0, val.find_first_not_of(" \r\n\t"));
        val.erase(val.find_last_not_of(" \r\n\t") + 1);
        that->env["REASON_PHRASE"] = val;
    } else {
        key.erase(key.find_last_of(':'));
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        getline(ss, val);
        val.erase(0, val.find_first_not_of(" \r\n\t"));
        val.erase(val.find_last_not_of(" \r\n\t") + 1);
        that->env[key] = val;
    }
    return nmemb;
}
}
