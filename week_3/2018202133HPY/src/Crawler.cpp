#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>

#include "EventLoop/EventLoop.hpp"
#include "Utils/URIHelper.hpp"

#include "Utils/Logger.hpp"
#include "Utils/Stat.hpp"

#include "Crawler.hpp"

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
        ret = cowr::Config::getInstance()["Global"]["savePath"] + std::string { path_match[1] };
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

    std::regex href_src_regex { "(href)=(\"[^\"]+\"|'[^']+'|[^\\s>)]+)", std::regex::icase };

    for (std::sregex_token_iterator it(data.begin(), data.end(), href_src_regex, 2),
         end;
         it != end;
         it++) {
        auto location = std::string(it->str());

        if (location[0] == '"' || location[0] == '\'')
            location = location.substr(1, location.size() - 2);

        bool next = false;
        for (auto ch : location) {
            if (ch == ':')
                next = true;
        }
        if (next)
            continue;

        location = location.substr(0, location.find_first_of('#'));

        location = (std::filesystem::path { location }).lexically_normal().string();

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
    std::function<void(std::vector<char>&, std::map<std::string, std::string>&, cowr::CurlEasyHandle&)> dataCallback,
    std::function<void(cowr::CurlEasyHandle&)> headerCallback)
{
    auto phandle = std::make_shared<cowr::CurlMultiHandle::SingleHandle>();

    auto buf = std::make_shared<std::vector<char>>();
    auto env = std::make_shared<std::map<std::string, std::string>>();

    phandle->setURL(url);
    phandle->setDataReceiveHandler(
        [buf](void* buffer, size_t, size_t nmemb, cowr::CurlEasyHandle&) -> size_t {
            buf->insert(buf->end(),
                (char*)buffer,
                (char*)buffer + nmemb);

            return nmemb;
        });
    phandle->setHeaderReceiveHandler([headerCallback, env](cowr::CurlEasyHandle& hand) -> void {
        *env = hand.getenv();
        headerCallback(hand);
    });
    phandle->setRequestDoneHandler(
        [buf, env, dataCallback, headerCallback](cowr::CurlEasyHandle& handle) -> void {
            if (auto psingle = dynamic_cast<cowr::CurlMultiHandle::SingleHandle*>(&handle); psingle) {
                if (psingle->isTLE()) {
                    auto&& url = psingle->getURL();
                    auto&& path = getSavePath(url);

                    //retry limit
                    if (cowr::Stat::getInstance().queryRequest(path) >= 65536) {
                        std::cerr << "retry limit exceeded... " << url << std::endl;
                    } else {
                        cowr::Stat::getInstance().incRequest(path);

                        cowr::EventLoop::getInstance().callLater(50, [url, dataCallback, headerCallback]() -> void {
                            addCurlHandle(url, dataCallback, headerCallback);
                        });
                    }
                } else
                    dataCallback(*buf, *env, handle);
            }
        });

    cowr::EventLoop::getInstance().addCurlHandle(phandle);
}

void processURL(std::string url)
{
    addCurlHandle(url,
        [url](std::vector<char>& buffer, std::map<std::string, std::string>&, cowr::CurlEasyHandle& handle) -> void {
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

                if (cowr::Stat::getInstance().queryRequest(save_path) == 0) {
                    cowr::Stat::getInstance().incRequest(save_path);
                    cowr::EventLoop::getInstance().callLater(0, std::bind(processURL, x));
                }
            }
        },
        [](cowr::CurlEasyHandle& handle) -> void {
            cowr::Stat::getInstance().incHeaderCounter();

            auto env = handle.getenv();
            auto code = env["STATUS_CODE"];

            auto pmhandle = dynamic_cast<cowr::CurlMultiHandle::SingleHandle*>(&handle);

            pmhandle->setHeaderDone();

            int level = cowr::Logger::DEBUG;
            std::string msg = code + ' ' + handle.getURL();

            if (code[0] == '3') {
                level = cowr::Logger::WARNING;
            } else if (code[0] == '2') {
                level = cowr::Logger::INFO;

                auto type = env["content-type"];

                msg += " [" + type + "] ";

                if (type.substr(0, type.find_first_of('/')) == "text") {
                    msg += "text, processing";
                } else {
                    msg += "not text, dropped";

                    if (pmhandle) {
                        pmhandle->remove(false);
                    } else {
                        throw ParamTypeError();
                    }
                }
            } else {
                cowr::Stat::getInstance().incDroppedCounter();

                level = cowr::Logger::ERROR;

                if (pmhandle) {
                    pmhandle->remove(false);
                } else {
                    throw ParamTypeError();
                }
            }

            msg = "(" + std::to_string(cowr::Stat::getInstance().queryHeader()) + ") " + msg;

            cowr::Logger::getInstance() << cowr::Logger::Message(level, msg);

            // std::cout << cowr::Stat::getInstance().queryHeader() << ' ' << '\t' << code << ' ' << handle.getURL() << std::endl;
        });
}
