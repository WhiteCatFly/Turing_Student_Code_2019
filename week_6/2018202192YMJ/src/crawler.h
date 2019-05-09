#ifndef CRAWLER_H_INCLUDED
#define CRAWLER_H_INCLUDED

class Crawler
{
private:
	static const std::string COMMAND_PREFIX;
	const int m_report_interval;
	const int m_backup_interval;
	timeval m_start_time;
	std::string get_file_name(const std::string &url) const;
	std::string get_cmd(const std::string &file_name,
						const std::string &url) const;
	void report(const std::queue<std::string> &webs_to_be_crawled);
	void write_log(const std::set<std::string> &visited_webs);
	void backup(const std::set<std::string> &visited_webs,
				std::queue<std::string> webs_to_be_crawled);
public:
	std::string m_homepage, m_save_path;
	int m_num_crawled, m_time_used;
	std::set<std::string> m_failed_urls;
	Crawler(const std::string &homepage,
			const std::string &save_path,
			int report_interval,
			int backup_interval);
	std::string crawl(const std::string &url);
	void expand(const std::string &cur_url,
				const std::string &file_name,
				std::set<std::string> &visited_webs,
				std::queue<std::string> &webs_to_be_crawled,
				const HTML_Parser &html_parser,
				const Normalizer &normalizer) const;
	void bfs_process(std::set<std::string> &visited_webs,
					 std::queue<std::string> &webs_to_be_crawled);
	virtual void bfs();
};

class Retrievable_Crawler: public Crawler
{
private:
	bool m_retry;
public:
	Retrievable_Crawler(const std::string &homepage,
						const std::string &save_path,
						int report_interval,
						int backup_interval,
						bool retry);
	virtual void bfs();
};

#endif