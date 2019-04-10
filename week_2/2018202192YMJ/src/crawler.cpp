#include <cstdlib>
#include <sys/time.h>

#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

#include "crawler.h"
#include "normalizer.h"
#include "href_extractor.h"

std::string get_file_name(const std::string &url,
						  const std::string &save_path)
{
	std::string file_name = save_path;
	for (auto i = url.find("/") + 1; i < url.size(); ++i)
	{
		if (url[i] == '/')
		{
			file_name += "__";
		}
		else
		{
			file_name += url[i];
		}
	}
	return file_name;
}

std::string get_cmd(const std::string &file_name,
					const std::string &url)
{
	const std::string COMMAND_PREFIX = "wget -o wget-log -t3 -T3 -O ";
	std::string cmd = COMMAND_PREFIX;
	cmd += escape(file_name);
	cmd += " ";
	cmd += escape(url);
	return cmd;
}

std::string crawl(const std::string &url, const std::string &save_path)
{
	auto file_name = get_file_name(url, save_path);
	auto cmd = get_cmd(file_name, url);
	if (system(cmd.c_str()))
	{
		std::cerr << "error: wget failed\n";
		std::cerr << "error command: " << cmd << "\n";
	}
	return file_name;
}

void bfs(const std::string &homepage,
		 const std::string &save_path)
{
	auto root_url = normalize_url(homepage, homepage, "/index.php");
	std::queue<std::string> webs_to_be_crwaled;
	std::set<std::string> visited_webs;
	webs_to_be_crwaled.push(root_url);
	visited_webs.insert(root_url);
	int num_crawled = 0;
	timeval start_time, now_time;
	gettimeofday(&start_time, NULL);
	while (!webs_to_be_crwaled.empty())
	{
		auto cur_url = webs_to_be_crwaled.front();
		webs_to_be_crwaled.pop();
		auto file_name = crawl(cur_url, save_path);
		++num_crawled;
		if (num_crawled % 10 == 0)
		{
			gettimeofday(&now_time, NULL);
			double time_used
				 = now_time.tv_sec - start_time.tv_sec
				 + (now_time.tv_usec - start_time.tv_usec) / CLOCKS_PER_SEC;
			std::cerr << num_crawled << " webs crawled, "
					  << webs_to_be_crwaled.size() << " webs in queue, "
					  << time_used << " seconds used\n";
		}
		std::vector<std::string> result;
		extract_href(file_name, result, homepage);
		for (auto href: result)
		{
			auto nxt_url = normalize_url(homepage, cur_url, href);
			if (visited_webs.find(nxt_url) == visited_webs.end())
			{
				webs_to_be_crwaled.push(nxt_url);
				visited_webs.insert(nxt_url);
			}
		}
	}
	gettimeofday(&now_time, NULL);
	double time_used
		 = now_time.tv_sec - start_time.tv_sec
		 + (now_time.tv_usec - start_time.tv_usec) / CLOCKS_PER_SEC;
	std::cerr << "total: " << num_crawled << " webs crawled, "
			  << time_used << " seconds used\n";
	std::ofstream fout("crawler-log");
	if (fout.is_open())
	{
		fout << "total: " << num_crawled << " webs crawled, "
			 << time_used << " seconds used" << "\n";
		std::cerr << "crawling log written successfully to \"crawler-log \"\n";
	}
	fout.close();
	fout.open("list.txt");
	if (fout.is_open())
	{
		for (auto ite = visited_webs.begin(); ite != visited_webs.end(); ++ite)
		{
			fout << *ite << '\n';
		}
	}
}
