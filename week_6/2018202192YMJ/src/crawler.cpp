#include <cstdlib>
#include <sys/time.h>

#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <iostream>

#include "normalizer.h"
#include "url_utility.h"
#include "html_parser.h"
#include "crawler.h"

const std::string Crawler::COMMAND_PREFIX \
				  = "wget -o wget-log -t3 -T3 -O ";

Crawler::Crawler(const std::string &homepage,
				 const std::string &save_path,
				 int report_interval,
				 int backup_interval):
	m_homepage(homepage), m_save_path(save_path),
	m_report_interval(report_interval),
	m_backup_interval(backup_interval)
{
	m_num_crawled = 0;
	m_time_used = 0;
}

std::string Crawler::get_file_name(const std::string &url) const
{
	std::string file_name = m_save_path;
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

void Crawler::report(const std::queue<std::string> &webs_to_be_crawled)
{
	timeval now_time;
	gettimeofday(&now_time, NULL);
	double time_used = m_time_used + now_time.tv_sec - m_start_time.tv_sec +
				 	   + (now_time.tv_usec - m_start_time.tv_usec) / CLOCKS_PER_SEC;
	std::clog << m_num_crawled << " webs crawled, "
			  << webs_to_be_crawled.size() << " webs in queue, "
			  << time_used << " seconds used" << std::endl;
}

void Crawler::write_log(const std::set<std::string> &visited_webs)
{
	timeval now_time;
	gettimeofday(&now_time, NULL);
	m_time_used += now_time.tv_sec - m_start_time.tv_sec
				 + (now_time.tv_usec - m_start_time.tv_usec) / CLOCKS_PER_SEC;
	std::clog << "total: " << m_num_crawled << " webs crawled, "
			  << m_time_used << " seconds used" << std::endl;
	std::ofstream fout("crawler-log");
	if (fout.is_open())
	{
		fout << "total: " << m_num_crawled << " webs crawled, "
			 << m_failed_urls.size() << "webs failed to crawl, "
			 << m_time_used << " seconds used" << "\n";
		std::clog << "crawling log written successfully to \"crawler-log\"\n";
	}
	else
	{
		std::cerr << "error: cannot open file \"crawler-log\"\n";
	}
	fout.close();
	fout.open("url_list.log");
	if (fout.is_open())
	{
		for (auto ite = visited_webs.begin(); ite != visited_webs.end(); ++ite)
		{
			fout << *ite << '\n';
		}
		std::clog << "list of urls written successfully to \"url_list.log\"\n";
	}
	else
	{
		std::cerr << "error: cannot open file \"url_list.log\"\n";
	}
	fout.close();
	fout.open("failed_urls.log");
	if(fout.is_open())
	{
		for (auto ite = m_failed_urls.begin(); ite != m_failed_urls.end(); ++ite)
		{
			fout << *ite << '\n';
		}
		std::clog << "list of failed urls written successfully to \"failed_urls.log\"\n";
	}
	else
	{
		std::cerr << "error: cannot open file \"failed_urls.log\"\n";
	}
	fout.close();
}

void Crawler::backup(const std::set<std::string> &visited_webs,
					 std::queue<std::string> webs_to_be_crawled)
{
	std::ofstream fout("backup.log");
	timeval now_time;
	gettimeofday(&now_time, NULL);
	m_time_used += now_time.tv_sec - m_start_time.tv_sec
				 + (now_time.tv_usec - m_start_time.tv_usec) / CLOCKS_PER_SEC;
	if (fout.is_open())
	{
		fout << m_homepage << " " << m_save_path << " "
			 << m_num_crawled << " " << m_time_used
			 << " " << visited_webs.size()
			 << " " << webs_to_be_crawled.size()
			 << " " << m_failed_urls.size()
			 << std::endl;
		for (const std::string &url: visited_webs)
		{
			fout << url << " ";
		}
		fout << std::endl;
		while (!webs_to_be_crawled.empty())
		{
			fout << webs_to_be_crawled.front() << " ";
			webs_to_be_crawled.pop();
		}
		fout << std::endl;
		for (const std::string &url: m_failed_urls)
		{
			fout << url << " ";
		}
		fout << std::endl;
	}
	else
	{
		std::cerr << "error: cannot open file \"backup.log\"\n";
	}
}

std::string Crawler::crawl(const std::string &url)
{
	auto file_name = get_file_name(url);
	auto cmd = get_cmd(file_name, url);
	if (system(cmd.c_str()))
	{
		std::cerr << "error: wget failed\n";
		std::cerr << "error command: " << cmd << "\n";
		m_failed_urls.insert(url);
	}
	return file_name;
}

void Crawler::expand(const std::string &cur_url,
			const std::string &file_name,
			std::set<std::string> &visited_webs,
			std::queue<std::string> &webs_to_be_crawled,
			const HTML_Parser &html_parser,
			const Normalizer &normalizer) const
{
	std::vector<std::string> result;
	html_parser.extract_href(file_name, result);
	for (auto href: result)
	{
		auto nxt_url = normalizer.normalize_url(cur_url, href);
		if (visited_webs.find(nxt_url) == visited_webs.end())
		{
			webs_to_be_crawled.push(nxt_url);
			visited_webs.insert(nxt_url);
		}
	}
}

void Crawler::bfs_process(std::set<std::string> &visited_webs,
						  std::queue<std::string> &webs_to_be_crawled)
{
	HTML_Parser html_parser(m_homepage);
	Normalizer normalizer(m_homepage);
	gettimeofday(&m_start_time, NULL);
	while (!webs_to_be_crawled.empty())
	{
		auto cur_url = webs_to_be_crawled.front();
		webs_to_be_crawled.pop();
		auto file_name = crawl(cur_url);
		++m_num_crawled;
		if (m_report_interval > 0 && m_num_crawled % m_report_interval == 0)
		{
			report(webs_to_be_crawled);
		}
		if (m_num_crawled % m_backup_interval == 0)
		{
			backup(visited_webs, webs_to_be_crawled);
			gettimeofday(&m_start_time, NULL);
		}
		expand(cur_url, file_name, visited_webs, webs_to_be_crawled,
			   html_parser, normalizer);
	}
	write_log(visited_webs);
}

void Crawler::bfs()
{
	auto root_url = m_homepage;
	std::set<std::string> visited_webs;
	std::queue<std::string> webs_to_be_crawled;
	visited_webs.insert(root_url);
	webs_to_be_crawled.push(root_url);
	bfs_process(visited_webs, webs_to_be_crawled);
}

Retrievable_Crawler::Retrievable_Crawler(const std::string &homepage,
										 const std::string &save_path,
										 int report_interval,
										 int backup_interval,
										 bool retry):
	Crawler(homepage, save_path, report_interval, backup_interval),
	m_retry(retry){}

void Retrievable_Crawler::bfs()
{
	std::ifstream fin("backup.log");
	if (fin.is_open())
	{
		std::set<std::string> visited_webs;
		std::queue<std::string> webs_to_be_crawled;
		int num_of_visited_webs;
		int num_of_webs_to_be_crawled;
		int num_of_failed_webs;
		fin >> m_homepage >> m_save_path
			>> m_num_crawled
			>> m_time_used
			>> num_of_visited_webs
			>> num_of_webs_to_be_crawled
			>> num_of_failed_webs;
		std::string url;
		for (int i = 0; i < num_of_visited_webs; ++i)
		{
			fin >> url;
			visited_webs.insert(url);
		}
		for (int i = 0; i < num_of_webs_to_be_crawled; ++i)
		{
			fin >> url;
			webs_to_be_crawled.push(url);
		}
		for (int i = 0; i < num_of_failed_webs; ++i)
		{
			fin >> url;
			m_failed_urls.insert(url);
		}
		if (!fin)
		{
			std::cerr << "fatal error: \"backup.log\" is not in the correct format\n";
			exit(1);
		}
		if(m_retry)
		{
			HTML_Parser html_parser(m_homepage);
			Normalizer normalizer(m_homepage);
			for (const std::string &url: m_failed_urls)
			{
				auto file_name = crawl(url);
				expand(url, file_name, visited_webs, webs_to_be_crawled,
					   html_parser, normalizer);
			}
		}
		bfs_process(visited_webs, webs_to_be_crawled);
	}
	else
	{
		std::cerr << "fatal error: cannot open \"backup.log\" to retrieve information\n";
		exit(1);
	}
}