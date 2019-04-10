#include <cctype>
#include <functional>
#include <iostream>
#include <set>
#include <typeinfo>

#include <unistd.h>

#include "HTMLParser/Parser.hpp"
#include "Utils/termutil.hpp"

void print_help(char* path)
{
    fprintf(stderr, R"HELPSTART(Usage: %s [-q query_string] [filename]%c)HELPSTART", path, '\n');
}

std::tuple<const char*, const char*> parse_arguments(int argc, char** argv)
{
    char* path = argv[0];
    char* selector = nullptr;
    char* filename = nullptr;

    char ch;
    while ((ch = getopt(argc, argv, "hq:")) != -1) {
        if (ch == 'h') {
            print_help(path);
            exit(0);
        } else if (ch == 'q') {
            selector = optarg;
        } else if (ch == '?') {
            if (optopt == 'q')
                std::cerr << "Option -q requires an argument." << std::endl;
            else
                std::cerr << "Unknown option -" << ch << std::endl;
            exit(1);
        } else {
            throw std::logic_error("Unknown return value of getopt");
        }
    }

    if (int index = optind; index < argc) {
        filename = argv[index];

        if (++index < argc) {
            std::cerr << "Unknown option " << argv[index] << std::endl;
            exit(1);
        }
    }

    return { selector, filename };
}

void HTMLPrintingHighlightTags(cowr::HTMLNonEmptyTagElement* root, cowr::HTMLElementList& highlights)
{
    std::function<
        void(cowr::HTMLTagElement*,
            std::set<cowr::HTMLTagElement*>&,
            int indent)>
        dfs = [&dfs](cowr::HTMLTagElement* now,
                  std::set<cowr::HTMLTagElement*>& highlights,
                  int indent) {
            for (int i = 0; i < indent; i++)
                std::cout << ' ';

            if (highlights.count(now))
                std::cout << cowr::TermUtil::setForeGroundColor(cowr::TermUtil::RED);
            std::cout << *now;
            if (highlights.count(now))
                std::cout << cowr::TermUtil::resetAttr();

            if (auto ptag = dynamic_cast<cowr::HTMLNonEmptyTagElement*>(now); ptag) {
                for (auto&& child : *ptag) {
                    if (auto pchild = dynamic_cast<cowr::HTMLTagElement*>(child.get()); pchild) {
                        std::cout << std::endl;
                        dfs(pchild, highlights, indent + 2);
                    } else {
                        std::cout << std::endl;
                        for (int i = 0; i < indent + 2; i++)
                            std::cout << ' ';
                        std::cout << cowr::convertToReference(child.get());
                    }
                }
            }
        };

    std::set<cowr::HTMLTagElement*> highlight_set;

    for (auto&& p : highlights)
        highlight_set.insert(dynamic_cast<cowr::HTMLTagElement*>(p));

    dfs(root, highlight_set, 0);
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    using namespace cowr;

    auto [selector, filename] = parse_arguments(argc, argv);

    std::unique_ptr<HTMLParser> parser;

    if (filename)
        parser = std::make_unique<HTMLParser>(std::filesystem::path(filename));
    else
        parser = std::make_unique<HTMLParser>(std::cin);

    auto pdocument = parser->parse();

    if (selector) {
        auto selected = pdocument->$(selector);
        HTMLPrintingHighlightTags(pdocument.get(), selected);
    } else {
        std::cout << pdocument->toColorfulString() << std::endl;
    }
}
