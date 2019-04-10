#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "string_utility.h"
#include "token.h"
#include "attribute.h"
#include "node.h"
#include "html_parser.h"

int main(int argc, char *argv[])
{
    std::string contents;
    HTML_Parser::Mode mode;
    for (int i = 1; i < argc; ++i)
    {
        if(argv[i][0] == '-')
        {
            char c = argv[i][1];
            ++i;
            if (i == argc)
            {
                std::cerr << "error: argument to \'-" << c
                          << "\' is missing (expected 1 value)\n";
                exit(1);
            }
            contents = argv[i];
            switch(c)
            {
            case 'u':
                mode = HTML_Parser::URL;
                break;
            case 'f':
                mode = HTML_Parser::FILE;
                break;
            case 's':
                mode = HTML_Parser::STRING;
                break;
            default:
                std::cerr << "error: unknown argument: -" << c << '\n';
                exit(1);
                break;
            }
        }
    }
    if (contents.empty())
    {
        std::cerr << "error: needs command line arguments to identify the contents to parse\n";
        exit(1);
    }
    HTML_Parser html_parser(contents, mode);
    html_parser.html_parse();
    std::ofstream fout("tree.txt");
    if (fout.is_open())
    {
        fout << html_parser << std::endl;
        std::clog << "tree structrue of the html has been printed to \"tree.txt\"" << std::endl;
    }
    else
    {
        std::cerr << "error: cannot open file \"tree.txt\"\n";
        exit(1);
    }
    html_parser.extract_specific_contents();
    html_parser.output_specific_contents();
    return 0;
}
