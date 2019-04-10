#ifndef _MENCI_WEB_CRAWLER_CRAWLER_H
#define _MENCI_WEB_CRAWLER_CRAWLER_H

#include <set>
#include <vector>
#include <regex>
#include "StringEx.h"
#include "Url.h"
#include "AsyncRequestPool.h"
#include "RequestOptions.h"

class Crawler {
    Url rootUrl;
    std::regex crawlingRegex;
    std::vector<StringEx> suffixBlackList;
    StringEx saveDirectory;
    StringEx indexSaveFilename;

    std::set<StringEx> crawledUrlSet;
    AsyncRequestPool pool;

    bool checkDuplicate(const Url &url);
    bool checkFiltered(const Url &newUrl);
    void extractUrls(const StringEx &str, const std::function<void(const StringEx&)> &callback);
    void savePage(const Url &url, const StringEx &data);
    void crawlUrl(const Url &url);

public:
    // onFilter(newUrl)
    // Return false to filter out newUrl.
    std::function<bool (const Url &)> onFilter;

    // onResponse(originUrl, redirectedUrl, responseBody, extracedUrls, skippedUrls, filteredUrls)
    // Return true to save.
    std::function<bool (const Url &,
                        const Url &,
                        const StringEx &,
                        std::vector<Url> &,
                        std::vector<Url> &)> onResponse;
    
    // onError(originUrl, redirectedUrl, errorMessage)
    std::function<void (const Url &, const Url &, const StringEx &)> onError;

    // onResponseIgnored(originUrl, redirectedUrl, message)
    std::function<void (const Url &, const Url &, const StringEx &)> onResponseIgnored;

    // onNewRequest(url)
    // Return false to stop the new request. Url can be modified.
    std::function<bool (Url &)> onNewRequest;

    Crawler(
        const Url &rootUrl,
        const StringEx &crawlingRegex,
        const std::vector<StringEx> &suffixBlackList,
        const StringEx &saveDirectory,
        const StringEx &indexSaveFilename,
        const RequestOptions &requestOptions
    ) : rootUrl(rootUrl),
        crawlingRegex((std::string)crawlingRegex, std::regex_constants::icase),
        suffixBlackList(suffixBlackList),
        saveDirectory(saveDirectory),
        indexSaveFilename(indexSaveFilename),
        pool(requestOptions)
    {}

    void crawl();
};

#endif // _MENCI_WEB_CRAWLER_CRAWLER_H
