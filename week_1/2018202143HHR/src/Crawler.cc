#include <cctype>
#include <queue>
#include <iostream>
#include <set>
#include <regex>
#include <functional>
#include <filesystem>
#include <fstream>

#include "AsyncRequestPool.h"
#include "UrlParser.h"
#include "TerminalColor.h"

const Url root("http://info.ruc.edu.cn");
AsyncRequestPool pool;
std::set<std::string> urlSet;
const std::regex reHref("href=\"(.*?)\"");
size_t crawlRequest = 0, crawled = 0, crawlError = 0;
std::list<std::pair<std::string, std::string>> errors;

void extractUrls(const std::string &str, const std::function<void(const std::string&)> &callback) {
    for (std::sregex_iterator it(str.begin(), str.end(), reHref); it != std::sregex_iterator(); it++) {
        auto &match = *it;
        callback(match[1]);
    }
}

bool checkSuffix(const std::string &str, const std::string &pattern) {
    if (str.length() < pattern.length()) return false;
    std::string suffix = str.substr(str.length() - pattern.length());
    for (size_t i = 0; i < pattern.length(); i++) {
        if (toupper(suffix[i]) != toupper(pattern[i])) return false;
    }
    return true;
}

bool checkPrefix(const std::string &str, const std::string &pattern) {
    if (str.length() < pattern.length()) return false;
    for (size_t i = 0; i < pattern.length(); i++) {
        if (toupper(str[i]) != toupper(pattern[i])) return false;
    }
    return true;
}

bool filterUrl(const Url &url) {
    static const std::string suffixBlackList[] = {
        ".css", ".js", ".png", ".jpg", ".jpeg", ".ico", ".avi", ".mp4", ".mp3", ".flv",
        ".xls", ".doc", ".ppt", ".xlsx", ".docx", ".pptx", ".pdf", ".rar", ".zip", ".7z"
    };
    
    for (auto &suffix : suffixBlackList) {
        if (checkSuffix(url.path, suffix)) return false;
    }

    if (checkPrefix(url.origin, "mailto:")) return false;
    if (checkPrefix(url.origin, "javascript:")) return false;
    if (url.host != root.host) return false;
    
    return true;
}

bool checkDuplicate(const Url &url) {
    std::string str = url.toRequestUrl();
    if (urlSet.count(str)) return false;
    urlSet.insert(str);
    return true;
}

void savePage(const Url &url, const std::string &data) {
    std::string pathString = "./output/" + url.host + url.path + url.query;
    if (pathString.back() == '/') pathString += "index.html";

    std::filesystem::path path = pathString;
    std::filesystem::create_directories(path.parent_path());

    std::ofstream fout(pathString);
    fout << data;
}

void crawlPage(Url url) {
    crawlRequest++;

    std::string requestUrl = url.toRequestUrl();
    pool.addTask(requestUrl, [requestUrl, url](std::string &error, std::string &responseBody) {
        crawled++;

        std::cout << "(" << BOLDWHITE << crawled << "/" << crawlRequest << RESET
                  << ", " << BOLDRED << crawlError << RESET << ") ";


        std::cout << requestUrl << std::endl;
        if (!error.empty()) {
            errors.push_back(std::make_pair(requestUrl, error));
            crawlError++;
            std::cout << BOLDRED << "\t\tError: " << RESET << error << std::endl;
            return;
        }

        std::cout << BOLDGREEN << "\t\tSuccess: " << RESET
                  << "length = " << BOLDWHITE << (double)responseBody.length() / 1024 << " KiB" << RESET << std::endl;

        savePage(url, responseBody);

        size_t extractedCount = 0, filteredCount = 0;
        extractUrls(responseBody, [&](const std::string &str) {
            extractedCount++;

            Url newUrl(str, url);
            if (filterUrl(newUrl) && checkDuplicate(newUrl)) {
                filteredCount++;
                crawlPage(newUrl);
            } else {
                // std::cout << "\tSkipped url: " << newUrl.toRequestUrl() << std::endl;
            }
        });

        std::cout << "\t\t" << BOLDWHITE << extractedCount << RESET << " url(s) extracted"
                  << ", " << BOLDWHITE << extractedCount - filteredCount << RESET << " skipped"
                  << ", " << BOLDWHITE << filteredCount << RESET << " filtered"
                  << std::endl;
    });
}

int main() {
    checkDuplicate(root);
    
    crawlPage(root);
    pool.runEventLoop();

    std::cout << BOLDRED << "Error URL(s):" << RESET << std::endl;
    for (auto pair : errors) {
        std::cout << '\t' << pair.first << ": " << BOLDWHITE << pair.second << RESET << std::endl;
    }
}
