#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <set>
#include <queue>
#include <string>
#include <iostream>

#include "crawler.h"
#include "normalizer.h"
#include "url_utility.h"
#include "href_extractor.h"

int main(int argc, char *argv[])
{
	const std::string HTTP = "http://";
	const std::string DEFAULT_HOMEPAGE = "econ.ruc.edu.cn/";
	const std::string DEFAULT_SAVE_PATH = "econ/";
	const int DEFAULT_REPORT_PERIOD = 10;
	std::string homepage = DEFAULT_HOMEPAGE;
	std::string save_path = DEFAULT_SAVE_PATH;
	int report_period = DEFAULT_REPORT_PERIOD;
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
			switch(c)
			{
			case 'h':
				homepage = argv[i];
				if (*homepage.rbegin() != '/') homepage += '/';
				if (is_absolute_url(homepage))
				{
					homepage = homepage.substr(HTTP.size());
				}
				break;
			case 'o':
				save_path = argv[i];
				if (*save_path.rbegin() != '/') save_path += '/';
				break;
			case 'p':
				sscanf(argv[i], "%d", &report_period);
				break;
			default:
				std::cerr << "unknown argument: -" << c << '\n';
				exit(1);
				break;
			}
		}
	}
	system(("mkdir " + save_path).c_str());
	Crawler crawler(homepage, save_path, report_period);
	crawler.bfs_from_homepage();
	return 0;
}
