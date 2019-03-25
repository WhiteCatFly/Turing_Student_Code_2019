#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

#include "EventLoop.hpp"
#include "URIHelper.hpp"

#include "Stat.hpp"

#include "Crawler.hpp"

inline Stat& global_stat = Stat::getStat();

void createParentDirectory(std::string pathstr)
{
    std::filesystem::path path(pathstr);
    pathstr = path.parent_path();
    pathstr = pathstr.substr(0, pathstr.find_last_not_of('/') + 1);
    std::filesystem::create_directories(pathstr);
}

std::string getBasename(std::string pathstr)
{
    std::filesystem::path path { pathstr };

    return path.filename();
}

std::string getSavePath(std::string url)
{
    std::filesystem::path path;
    std::string ret;
    std::regex path_regex { "[^:]+://[^/]+/+(.*)" };

    std::smatch path_match;
    if (std::regex_search(url, path_match, path_regex)) {
        ret = Config::global_config["Global"]["savePath"] + std::string { path_match[1] };
        path = ret;
        if (!path.has_extension())
            path /= "index.html";
        if (!path.has_filename())
            path += "index.html";

        return path;
    }

    throw URLParseError();
}

std::string getPath(std::string url)
{
    std::filesystem::path path;
    std::string ret;
    std::regex path_regex { "[^:]+://[^/]+/+(.*)" };

    std::smatch path_match;
    if (std::regex_search(url, path_match, path_regex)) {
        return path_match[1];
    }

    throw URLParseError();
}

std::string getProto(std::string url)
{
    std::regex path_regex { "([^:]+)://[^/]+/+.*" };

    std::smatch path_match;
    if (std::regex_search(url, path_match, path_regex)) {
        return path_match[1];
    };
    throw URLParseError();
}

std::string getSite(std::string url)
{
    std::regex path_regex { "[^:]+://([^/]+)/+.*" };

    std::smatch path_match;
    if (std::regex_search(url, path_match, path_regex)) {
        return path_match[1];
    };
    throw URLParseError();
}

std::vector<std::string> findURLs(std::string proto,
    std::string site,
    std::string path,
    std::string data)
{
    auto nowPrefix = proto + "://" + site + "/" + path;
    nowPrefix = nowPrefix.substr(0, nowPrefix.find_last_of('/') + 1);
    std::vector<std::string> ret;
    std::regex href_src_regex { "(href|src)=\"([^\"]*)\"" };

    for (std::sregex_token_iterator it(data.begin(), data.end(), href_src_regex, 2),
         end;
         it != end;
         it++) {
        auto location = std::string(it->str());

        bool next = false;
        for (auto ch : location) {
            if (ch == ':')
                next = true;
        }
        if (next)
            continue;

        location = location.substr(0, location.find_first_of('#'));
        try {
            if (getSite(location) != site)
                continue;
        } catch (URLParseError) {

            if (location[0] != '/')
                location = nowPrefix + location;
            else
                location = proto + "://" + site + location;
        }
        ret.push_back(location);
    }

    return ret;
}

void addCurlHandle(std::string url,
    std::function<void(std::vector<char>&, std::map<std::string, std::string>&, CurlEasyHandle&)> dataCallback,
    std::function<void(CurlEasyHandle&)> headerCallback)
{
    auto phandle = std::make_shared<CurlMultiHandle::SingleHandle>();

    auto buf = std::make_shared<std::vector<char>>();
    auto env = std::make_shared<std::map<std::string, std::string>>();

    phandle->setURL(url);
    phandle->setDataReceiveHandler(
        [buf](void* buffer, size_t, size_t nmemb, CurlEasyHandle&) -> size_t {
            buf->insert(buf->end(),
                (char*)buffer,
                (char*)buffer + nmemb);

            return nmemb;
        });
    phandle->setHeaderReceiveHandler([headerCallback, env](CurlEasyHandle& hand) -> void {
        *env = hand.getenv();
        headerCallback(hand);
    });
    phandle->setRequestDoneHandler(
        [buf, env, dataCallback, headerCallback](CurlEasyHandle& handle) -> void {
            if (auto psingle = dynamic_cast<CurlMultiHandle::SingleHandle*>(&handle); psingle) {
                if (psingle->isTLE()) {
                    auto&& url = psingle->getURL();
                    auto&& path = getSavePath(url);

                    //retry limit
                    if (global_stat.queryRequest(path) >= 65536) {
                        std::cerr << "retry limit exceeded... " << url << std::endl;
                    } else {
                        global_stat.incRequest(path);

                        global_loop.callLater(50, [url, dataCallback, headerCallback]() -> void {
                            addCurlHandle(url, dataCallback, headerCallback);
                        });
                    }
                } else
                    dataCallback(*buf, *env, handle);
            }
        });

    global_loop.addCurlHandle(phandle);
}

void processURL(std::string url)
{
    addCurlHandle(url,
        [url](std::vector<char>& buffer, std::map<std::string, std::string>&, CurlEasyHandle& handle) -> void {
            auto path = getSavePath(url);
            createParentDirectory(path);
            std::ofstream out(path);

            out.write(buffer.data(), buffer.size());
            out.flush();

            buffer.push_back('\0');
            std::string context { buffer.data() };

            auto now_url = handle.getURL();
            auto urls = findURLs(getProto(now_url),
                getSite(now_url),
                getPath(now_url),
                context);

            for (auto x : urls) {
                auto save_path = getSavePath(x);

                std::filesystem::path file { save_path };

                auto&& ext = file.extension();

                if (ext == ".png" || ext == ".jpg" || ext == ".flv" || ext == ".rar" || ext == ".doc")
                    continue;

                if (global_stat.queryRequest(save_path) == 0) {
                    global_stat.incRequest(save_path);
                    global_loop.callLater(0, std::bind(processURL, x));
                }
            }
        },
        [](CurlEasyHandle& handle) -> void {
            global_stat.incHeaderCounter();

            auto env = handle.getenv();
            auto code = env["STATUS_CODE"];

            auto pmhandle = dynamic_cast<CurlMultiHandle::SingleHandle*>(&handle);

            pmhandle->setHeaderDone();

            if (code[0] == '3') {
                ;
                // std::cout << TERM_FRONT_YELLOW << code << TERM_DEFAULT << ' ' << handle.getURL() << ' ' << header_counter << std::endl;
            } else if (code[0] == '2') {
                // std::cout << TERM_FRONT_GREEN << code << TERM_DEFAULT << ' ' << handle.getURL() << ' ' << header_counter << std::endl;
                auto type = env["content-type"];

                // std::cout << "[" << type << "] ";

                if (type.substr(0, type.find_first_of('/')) == "text") {
                    // std::cout << "text, processing";
                } else {
                    // std::cout << "not text, dropped";

                    if (pmhandle) {
                        pmhandle->remove(false);
                    } else {
                        throw ParamTypeError();
                    }
                }
            } else {
                global_stat.incDroppedCounter();
                // std::cout << TERM_FRONT_RED << code << TERM_DEFAULT << ' ' << handle.getURL() << ' ' << header_counter << std::endl;

                if (pmhandle) {
                    pmhandle->remove(false);
                } else {
                    throw ParamTypeError();
                }
            }

            std::cout << global_stat.queryHeader() << ' ' << '\t' << code << ' ' << handle.getURL() << std::endl;
        });
}
