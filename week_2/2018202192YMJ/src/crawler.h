#ifndef CRAWLER_H_INCLUDED
#define CRAWLER_H_INCLUDED

std::string get_file_name(const std::string &url,
						  const std::string &save_path);
std::string get_cmd(const std::string &file_name,
					const std::string &url);
std::string crawl(const std::string &url);
void bfs(const std::string &homepage, const std::string &save_path);

#endif