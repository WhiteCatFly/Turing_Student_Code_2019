#include <regex>
#include <filesystem>
#include <fstream>
#include "Crawler.h"

bool Crawler::checkDuplicate(const Url &url) {
    const StringEx str = url.toString();
    if (this->crawledUrlSet.count(str)) return true;
    this->crawledUrlSet.insert(str);
    return false;
}

bool Crawler::checkFiltered(const Url &newUrl) {
    if (newUrl.origin.startsWith("about:", true)) return true;
    if (newUrl.origin.startsWith("mailto:", true)) return true;
    if (newUrl.origin.startsWith("javascript:", true)) return true;
    if (newUrl.host != this->rootUrl.host) return true;

    for (auto &suffix : this->suffixBlackList) {
        if (newUrl.path.endsWith(suffix, true)) return true;
    }

    if (this->onFilter && this->onFilter(newUrl)) return true;
    
    return false;
}

void Crawler::extractUrls(const StringEx &str, const std::function<void(const StringEx&)> &callback) {
    for (std::sregex_iterator it(str.begin(), str.end(), crawlingRegex); it != std::sregex_iterator(); it++) {
        auto &match = *it;

        for (size_t i = 1; i < match.size(); i++) {
            StringEx str = match[i];
            if (str.length()) {
                callback(str);
                break;
            }
        }
    }
}

void Crawler::savePage(const Url &url, const StringEx &data) {
    StringEx pathString = this->saveDirectory + '/' + url.host + url.path + url.query;
    if (pathString.back() == '/') pathString += indexSaveFilename;

    const std::filesystem::path path = (std::string)pathString;
    std::filesystem::create_directories(path.parent_path());

    std::ofstream fout(pathString);
    fout << data;
}

void Crawler::crawlUrl(const Url &url) {
    pool.addTask(url, [this, url](bool error, const StringEx &errorMessage, const StringEx &responseBody, const Url &redirectedUrl) {
        if (error) {
            if (this->onError) {
                this->onError(url, redirectedUrl, errorMessage);
            }
            return;
        }

        // If redirected URL is filtered, ignore it.
        if (this->checkFiltered(redirectedUrl)) {
            if (this->onResponseIgnored) {
                this->onResponseIgnored(url, redirectedUrl, "Redirected URL filtered out.");
            }
            return;
        }

        // Extract urls.
        std::vector<Url> skippedUrls, validUrls;
        extractUrls(responseBody, [&](const StringEx &str) {
            Url newUrl(str, redirectedUrl);
            if (!this->checkFiltered(newUrl) && !this->checkDuplicate(newUrl)) {
                validUrls.push_back(std::move(newUrl));
            } else {
                skippedUrls.push_back(std::move(newUrl));
            }
        });

        // Call callback.
        if (!this->onResponse || this->onResponse(url, redirectedUrl, responseBody, skippedUrls, validUrls)) {
            this->savePage(redirectedUrl, responseBody);
        }

        // Add new requests.
        for (Url &newUrl : validUrls) {
            if (!this->onNewRequest || this->onNewRequest(newUrl)) {
                this->crawlUrl(newUrl);
            }
        }
    });
}

void Crawler::crawl() {
    // Root url can't be canceled.
    this->checkDuplicate(this->rootUrl);
    if (this->onNewRequest) {
        this->onNewRequest(this->rootUrl);
    }

    this->crawlUrl(this->rootUrl);

    this->pool.runEventLoop();
}
