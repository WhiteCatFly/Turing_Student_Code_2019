#include <cstring>

#include <string>
#include <iostream>

#include "crawler.h"
#include "normalizer.h"
#include "href_extractor.h"

int main(int argc, char *argv[])
{
	const std::string DEFAULT_HOMEPAGE = "info.ruc.edu.cn/";
	std::string homepage = DEFAULT_HOMEPAGE;
	const std::string DEFAULT_SAVE_PATH = "pages/";
	std::string save_path = DEFAULT_SAVE_PATH;
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
				return 0;
			}
			switch(c)
			{
			case 'h':
				homepage = argv[i];
				if (*homepage.rbegin() != '/') homepage += '/';
				if (is_absolute_url(homepage))
				{
					homepage = homepage.substr(strlen("http://"));
				}
				break;
			case 'o':
				save_path = argv[i];
				if (*save_path.rbegin() != '/') save_path += '/';
				break;
			default:
				std::cerr << "unknown argument: -" << c << '\n';
				break;
			}
		}
	}
	bfs(homepage, save_path);
	return 0;
}
