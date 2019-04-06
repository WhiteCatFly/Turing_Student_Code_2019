#include <cstdlib>
#include <sys/time.h>

#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

#include "crawler.h"
#include "normalizer.h"
#include "url_utility.h"
#include "href_extractor.h"

const std::string Crawler::COMMAND_PREFIX \
				  = "wget -o wget-log -t5 -T5 -O ";

Crawler::Crawler(const std::string &homepage__,
				 const std::string &save_path__,
				 int report_period__ = 10) :
	homepage(homepage__), save_path(save_path__),
	report_period(report_period__)
{
	num_crawled = 0;
	gettimeofday(&start_time, NULL);
}

std::string Crawler::get_file_name(const std::string &url) const
{
	std::string file_name = save_path;
	for (int i = 0; i < url.size(); ++i)
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

std::string Crawler::get_cmd(const std::string &file_name,
							 const std::string &url) const
{
	std::string cmd = COMMAND_PREFIX;
	cmd += escape(file_name);
	cmd += " ";
	cmd += escape(url);
	return cmd;
}

void Crawler::report(const std::queue<std::string> &webs_to_be_crawled) const
{
	timeval now_time;
	gettimeofday(&now_time, NULL);
	double time_used
		 = now_time.tv_sec - start_time.tv_sec
		 + (now_time.tv_usec - start_time.tv_usec) / CLOCKS_PER_SEC;
	std::clog << num_crawled << " webs crawled, "
			  << webs_to_be_crawled.size() << " webs in queue, "
			  << time_used << " seconds used" << std::endl;
}

void Crawler::write_log(const std::set<std::string> &visited_webs) const
{
	timeval now_time;
	gettimeofday(&now_time, NULL);
	double time_used
		 = now_time.tv_sec - start_time.tv_sec
		 + (now_time.tv_usec - start_time.tv_usec) / CLOCKS_PER_SEC;
	std::clog << "total: " << num_crawled << " webs crawled, "
			  << time_used << " seconds used" << std::endl;
	std::ofstream fout("crawler-log");
	if (fout.is_open())
	{
		fout << "total: " << num_crawled << " webs crawled, "
			 << time_used << " seconds used" << "\n";
		std::clog << "crawling log written successfully to \"crawler-log\"" << std::endl;
	}
	fout.close();
	fout.open("url_list.txt");
	if (fout.is_open())
	{
		for (auto ite = visited_webs.begin(); ite != visited_webs.end(); ++ite)
		{
			fout << *ite << '\n';
		}
		std::clog << "list of urls written successfully to \"url_list.txt\"" << std::endl;
	}
}

std::string Crawler::crawl(const std::string &url) const
{
	auto file_name = get_file_name(url);
	auto cmd = get_cmd(file_name, url);
	if (system(cmd.c_str()))
	{
		std::cerr << "error: wget failed\n";
		std::cerr << "error command: " << cmd << "\n";
	}
	return file_name;
}

void Crawler::bfs_from_homepage()
{
	auto root_url = homepage;
	std::queue<std::string> webs_to_be_crawled;
	std::set<std::string> visited_webs;
	webs_to_be_crawled.push(root_url);
	visited_webs.insert(root_url);
	std::ofstream trace("trace.txt");
	Href_Extractor href_extractor(homepage);
	Normalizer normalizer(homepage);
	while (!webs_to_be_crawled.empty())
	{
		auto cur_url = webs_to_be_crawled.front();
		webs_to_be_crawled.pop();
		auto file_name = crawl(cur_url);
		++num_crawled;
		if (report_period > 0 && num_crawled % report_period == 0)
		{
			report(webs_to_be_crawled);
		}
		std::vector<std::string> result;
		href_extractor.extract_href(file_name, result);
		for (auto href: result)
		{
			auto nxt_url = normalizer.normalize_url(cur_url, href);
			if (visited_webs.find(nxt_url) == visited_webs.end())
			{
				if (trace.is_open())
				{
					trace << cur_url << " -> " << nxt_url << std::endl;
				}
				webs_to_be_crawled.push(nxt_url);
				visited_webs.insert(nxt_url);
			}
		}
	}
	if (trace.is_open())
	{
		std::clog << "trace of bfs written successfully to \"trace.txt\"" << std::endl;
	}
	write_log(visited_webs);
}
