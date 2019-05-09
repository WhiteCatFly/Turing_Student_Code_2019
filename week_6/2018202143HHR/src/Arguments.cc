#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <functional>
#include <filesystem>

#include "Arguments.h"
#include "Url.h"
#include "ArgumentParser.h"

Arguments parseArguments(int argc, char *argv[]) {
    Arguments arguments;
    ArgumentParser(argc, argv)
        .setProgramDescription("A web crawler to download a website's all webpages.")
        .addPositional("root_url", "The beginning webpage's URL.",
                       ArgumentParser::stringParser(arguments.rootUrl, [](const StringEx &url) -> std::optional<StringEx> {
                           try {
                               (Url(url));
                               return std::nullopt;
                           } catch (const std::logic_error &e) {
                               return StringEx(e.what());
                           }
                       }))
        .addOption("output-directory", "o", "path",
                   "The directory to save crawled pages.",
                   ArgumentParser::stringParser(arguments.outputDirectory, [](const StringEx &path) -> std::optional<StringEx> {
                       try {
                           std::filesystem::create_directories((std::string)path);
                           return std::nullopt;
                       } catch (const std::filesystem::filesystem_error &e) {
                           return StringEx(e.what());
                       }
                   }))
        .addOption("index-save-filename", "i", "filename",
                   "The filename used when saving a directory's index page.",
                   ArgumentParser::stringParser(arguments.indexSaveFilename),
                   true, "index.html")
        .addOption("use-regex", "R", "",
                   "Use regex instead of HTMLParser to get a page's next URLs to crawl.",
                   ArgumentParser::boolParser(arguments.useRegex),
                   true)
        .addOption("crawling-regex", "r", "regex",
                   "The regex used to find a page's next URLs to crawl, matches case-insensitive. First non-empty capture group's value is used.",
                   ArgumentParser::stringParser(arguments.crawlingRegex),
                   true, "href\\s*=\\s*(?:\"(.*?)\"|'(.*?)'|([^>\\s\"']+))")
        .addOption("suffix-black-list", "b", "list",
                   "A list of filename suffixes that shouldn't be crawled, separated with comma.",
                   ArgumentParser::stringParser(arguments.suffixBlackList),
                   true, ".css,.js,.png,.jpg,.bmp,.gif,.jpeg,.ico,.avi,.mp4,.mp3,.xls,.flv,.doc,.ppt,.xlsx,.docx,.pptx,.pdf,.rar,.zip,.7z")
        .addOption("wget-command", "W", "path",
                   "The wget command path, if not in $PATH.",
                   ArgumentParser::stringParser(arguments.requestOptions.wgetCommand, [](const StringEx &path) -> std::optional<StringEx> {
                       // Check if wget is available.
                       constexpr int EXIT_WGET_UNAVAILABLE = 127;
                       const pid_t pid = vfork();
                       if (pid < 0) {
                           perror("vfork");
                           abort();
                       } else if (pid > 0) {
                           // Parent.

                           int status;
                           waitpid(pid, &status, 0);
                           if (!WIFEXITED(status) || WEXITSTATUS(status) == EXIT_WGET_UNAVAILABLE) {
                               return "Can't invoke wget";
                           }
                       } else {
                           // Child.
                           close(STDIN_FILENO);
                           close(STDOUT_FILENO);
                           close(STDERR_FILENO);
                           execlp(path.getData(), path.getData(), NULL);
                           exit(EXIT_WGET_UNAVAILABLE);
                       }
                       return std::nullopt;
                   }),
                   true, "wget")
        .addOption("max-concurrent-count", "m", "value",
                   "The maximum concurrent wget process count.",
                   ArgumentParser::integerParser(arguments.requestOptions.maxConcurrenteCount),
                   true, "40")
        .addOption("wget-timeout", "t", "value",
                   "Timeout of a HTTP request.", 
                   ArgumentParser::integerParser(arguments.requestOptions.wgetTimeout),
                   true, "10")
        .addOption("wget-waitretry", "w", "value", "Wait time before retry a failed HTTP request.",
                   ArgumentParser::integerParser(arguments.requestOptions.wgetWaitRetry),
                   true, "0")
        .addOption("wget-tries", "n", "value", "Maximum tries of a HTTP request.", 
                   ArgumentParser::integerParser(arguments.requestOptions.wgetTries),
                   true, "20")
        .parse();
    return arguments;
}
