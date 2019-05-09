#include <list>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "StringEx.h"
#include "Arguments.h"
#include "Crawler.h"
#include "TerminalColor.h"

using namespace std::chrono_literals;

int main(int argc, char *argv[]) {
    Arguments arguments = parseArguments(argc, argv);

    Crawler crawler(
        arguments.rootUrl,
        arguments.useRegex,
        arguments.crawlingRegex,
        arguments.suffixBlackList.split(','),
        arguments.outputDirectory,
        arguments.indexSaveFilename,
        arguments.requestOptions
    );

    // Set floating-point for logging output.
    std::cout << std::fixed << std::setprecision(2);

    // Record each request's finish time, to calculate RPS.
    constexpr size_t FINISHED_REQUESTS_RESERVE_SPACE = 10000;
    std::vector<std::chrono::steady_clock::time_point> finishedRequests;
    finishedRequests.reserve(FINISHED_REQUESTS_RESERVE_SPACE);

    auto addFinishedRequest = [&]() {
        finishedRequests.push_back(std::chrono::steady_clock::now());
    };

    const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    std::list<std::pair<Url, StringEx>> errors;
    size_t requestCount = 0, errorCount = 0, ignoredCount = 0;

    // e.g. (20/100, 70 RPS, 68.42 Average RPS, 3) /path/page.html
    auto logUrl = [&](const Url &originUrl, const Url &redirectedUrl) {
        std::cout << TerminalColor::Reset
                  << "("
                  << TerminalColor::Bold << TerminalColor::ForegroundWhite
                  << finishedRequests.size() << "/" << requestCount
                  << TerminalColor::Reset
                  << ", ";
        
        const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        const size_t rps = finishedRequests.end()
                         - std::upper_bound(finishedRequests.begin(),
                                            finishedRequests.end(),
                                            currentTime - 1s);
        const double elapsedTime = std::chrono::duration<double>(currentTime - startTime).count();
        const double averageRPS = finishedRequests.size() / elapsedTime;
        std::cout << TerminalColor::Reset
                  << TerminalColor::Bold << TerminalColor::ForegroundGreen
                  << rps
                  << TerminalColor::Bold << TerminalColor::ForegroundWhite
                  << " RPS"
                  << TerminalColor::Reset
                  << ", "
                  << TerminalColor::Bold << TerminalColor::ForegroundGreen
                  << averageRPS
                  << TerminalColor::Bold << TerminalColor::ForegroundWhite
                  << " Average RPS";

        if (errorCount > 0) {
            std::cout << TerminalColor::Reset
                      << ", "
                      << TerminalColor::Bold << TerminalColor::ForegroundRed
                      << errorCount;
        }

        std::cout << TerminalColor::Reset
                  << ") " << originUrl.toString(true);
        
        if (redirectedUrl.toString() != originUrl.toString()) {
            std::cout << TerminalColor::Bold << TerminalColor::ForegroundYellow
                      << " => "
                      << TerminalColor::Reset
                      << redirectedUrl.toString(true);
        }

        std::cout << ' ';
    };

    crawler.onError = [&](const Url &originUrl, const Url &redirectedUrl, const StringEx &errorMessage) {
        addFinishedRequest();
        errorCount++;

        logUrl(originUrl, redirectedUrl);
        std::cout << TerminalColor::Bold << TerminalColor::ForegroundRed
                  << "ERROR"
                  << TerminalColor::Reset
                  << ' ' << errorMessage
                  << std::endl;
        
        errors.push_back(std::make_pair(redirectedUrl, errorMessage));
    };

    crawler.onResponseIgnored = [&](const Url &originUrl,
                                    const Url &redirectedUrl,
                                    const StringEx &message) {
        addFinishedRequest();
        ignoredCount++;

        logUrl(originUrl, redirectedUrl);
        std::cout << TerminalColor::Bold << TerminalColor::ForegroundGreen
                  << "OK"
                  << TerminalColor::Reset
                  << " Response ignored: " << message << '.'
                  << std::endl;

        return true;
    };

    crawler.onResponse = [&](const Url &originUrl,
                             const Url &redirectedUrl,
                             const StringEx &responseBody,
                             std::vector<Url> &skippedUrls,
                             std::vector<Url> &validUrls) -> bool {
        addFinishedRequest();

        logUrl(originUrl, redirectedUrl);
        std::cout << TerminalColor::Bold << TerminalColor::ForegroundGreen
                  << "OK"
                  << TerminalColor::Bold << TerminalColor::ForegroundWhite
                  << ' ' << (double)responseBody.length() / 1024 << " KiB"
                  << TerminalColor::Reset;

        const size_t extractedUrlCount = skippedUrls.size() + validUrls.size();
        if (extractedUrlCount > 0) {
            std::cout << ", "
                      << TerminalColor::Bold << TerminalColor::ForegroundWhite
                      << extractedUrlCount
                      << TerminalColor::Reset
                      << " URL(s) extracted";

            if (validUrls.size() > 0) {
                std::cout << TerminalColor::Reset
                          << ", "
                          << TerminalColor::Bold << TerminalColor::ForegroundWhite
                          << validUrls.size()
                          << TerminalColor::Reset
                          << " followed";
            }
        }

        std::cout << std::endl;

        return true;
    };

    crawler.onNewRequest = [&](Url &url) -> bool {
        requestCount++;
        return true;
    };

    crawler.crawl();

    std::cout << std::endl;

    if (!errors.empty()) {
        std::cout << TerminalColor::Bold << TerminalColor::ForegroundRed
                  << "Error(s)"
                  << TerminalColor::Reset
                  << ':'
                  << std::endl;
        for (auto pair : errors) {
            std::cout << TerminalColor::Reset
                      << "    " << pair.first.toString() << ": "
                      << TerminalColor::Bold << TerminalColor::ForegroundWhite
                      << pair.second
                      << TerminalColor::Reset
                      << std::endl;
        }
    }

    const double elapsedTime = std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count();
    std::cout << TerminalColor::Reset
              << std::endl
              << "Finished crawling in "
              << TerminalColor::Bold << TerminalColor::ForegroundWhite
              << elapsedTime
              << TerminalColor::Reset
              << " seconds, "
              << TerminalColor::Bold << TerminalColor::ForegroundGreen
              << finishedRequests.size() / elapsedTime
              << TerminalColor::Reset
              << " average RPS, "
              << TerminalColor::Bold << TerminalColor::ForegroundGreen
              << finishedRequests.size() - errors.size() - ignoredCount
              << TerminalColor::Reset
              << " success URL(s), "
              << TerminalColor::Bold << TerminalColor::ForegroundRed
              << errors.size()
              << TerminalColor::Reset
              << " error(s) in total."
              << std::endl;
}
