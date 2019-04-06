#ifndef CRAWLER_H_INCLUDED
#define CRAWLER_H_INCLUDED

class Crawler
{
private:
	static const std::string COMMAND_PREFIX;
	const int report_period;
	const std::string homepage, save_path;
	int num_crawled;
	timeval start_time;
	std::string get_file_name(const std::string &url) const;
	std::string get_cmd(const std::string &file_name,
						const std::string &url) const;
	void report(const std::queue<std::string> &webs_to_be_crawled) const;
	void write_log(const std::set<std::string> &visited_webs) const;
public:
	Crawler(const std::string &homepage__,
			const std::string &save_path__,
			int report_period__);
	~Crawler(){}
	std::string crawl(const std::string &url) const;
	void bfs_from_homepage();
};

#endif