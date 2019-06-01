#include <iostream>

#include "HTMLParser/Parser.hpp"

int main(int argc, char** argv)
{
    if (argc <= 1 || argc >= 3) {
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    cowr::HTMLParser parser { std::filesystem::path(argv[1]) };

    auto dom = parser.parse();

    auto bodies = dom->$("body");

    for (auto body : bodies) {
        std::cout << body->innerText() << std::endl;
    }
}
