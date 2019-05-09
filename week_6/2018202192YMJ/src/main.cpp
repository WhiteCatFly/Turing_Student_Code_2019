#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <set>
#include <queue>
#include <string>
#include <iostream>

#include "html_parser.h"
#include "normalizer.h"
#include "crawler.h"
#include "url_utility.h"
#include "string_utility.h"

int main(int argc, char *argv[])
{
	const std::string HTTP = "http://";
	const std::string DEFAULT_HOMEPAGE = "info.ruc.edu.cn/";
	const std::string DEFAULT_SAVE_PATH = "info/";
	const int DEFAULT_REPORT_INTERVAL = 10;
	const int DEFAULT_BACKUP_INTERVAL = 100;
	std::string homepage = DEFAULT_HOMEPAGE;
	std::string save_path = DEFAULT_SAVE_PATH;
	int report_interval = DEFAULT_REPORT_INTERVAL;
	int backup_intetval = DEFAULT_BACKUP_INTERVAL;
	bool retrieve = false;
	bool retry = false;
	for (int i = 1; i < argc; ++i)
	{
		if(argv[i][0] == '-')
		{
			char c = argv[i][1];
			if (c != 'c' && c != 'r')
			{
				++i;
				if (i == argc)
				{
					std::cerr << "fatal error: argument to \'-" << c
							  << "\' is missing (expected 1 value)\n";
					exit(1);
				}
			}
			switch(c)
			{
			case 'b':
				sscanf(argv[i], "%d", &backup_intetval);
				break;
			case 'c':
				retrieve = true;
				break;
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
				sscanf(argv[i], "%d", &report_interval);
				break;
			case 'r':
				retrieve = retry = true;
				break;
			default:
				std::cerr << "fatal error: unknown argument -" << c << '\n';
				exit(1);
				break;
			}
		}
	}
	system(("mkdir " + save_path).c_str());
	if (retrieve)
	{
		Retrievable_Crawler retrievable_crawler(homepage, save_path,
												report_interval, backup_intetval, retry);
		retrievable_crawler.bfs();
	}
	else
	{
		Crawler crawler(homepage, save_path, report_interval, backup_intetval);
		crawler.bfs();
	}
	return 0;
}
