#include <ctime>
#include <cstdlib>
#include <sys/time.h>

#include <set>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

void bfs()
{
	extern std::string homepage;
	extern std::string normalize_url(std::string, std::string);
	auto root_url = normalize_url(homepage, "/index.php");
	std::queue<std::string> que;
	std::set<std::string> visited;
	que.push(root_url);
	visited.insert(root_url);
	int num_crawled = 0;
	while (!que.empty())
	{
		auto cur_url = que.front();
		que.pop();
		extern std::string crawl(std::string);
		auto file_name = crawl(cur_url);
		++num_crawled;
		if (num_crawled % 10 == 0)
		{
			extern timeval start_time, now_time;
			gettimeofday(&now_time, NULL);
			double time_used = now_time.tv_sec - start_time.tv_sec + (now_time.tv_usec - start_time.tv_usec) / CLOCKS_PER_SEC;
			std::cerr << num_crawled << " webs crawled, " << que.size() << " webs in queue, " << time_used << " seconds used" << "\n";
		}
		extern std::vector<std::string> extract_href_from_file(std::string);
		for (auto href: extract_href_from_file(file_name))
		{
			auto nxt_url = normalize_url(cur_url, href);
			if (visited.find(nxt_url) != visited.end())
			{
				continue;
			}
			que.push(nxt_url);
			visited.insert(nxt_url);
		}
	}
	extern timeval start_time, now_time;
	gettimeofday(&now_time, NULL);	
	double time_used = now_time.tv_sec - start_time.tv_sec + (now_time.tv_usec - start_time.tv_usec) / CLOCKS_PER_SEC;
	std::cerr << "total: " << num_crawled << " webs crawled, " << time_used << " seconds used" << "\n";
	std::ofstream fout("crawler_log");
	if (fout.is_open())
	{
		fout << "total: " << num_crawled << " webs crawled, " << time_used << " seconds used" << "\n";
	}
}

