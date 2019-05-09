#ifndef CRAWL_H_INCLUDED
#define CRAWL_H_INCLUDED

class Crawler {
private:
	const static std::string black_list[];
	timeval start_time;
	const std::string  download_path, save_file_path;
	const Url root_url;
	std::queue<Url> waiting_urls;
	std::set<Url> visited_urls;
	void set_start_time();
	int check_file_size(std::string path) const{
		std::ifstream strm;
		strm.open(path);
		if (!strm) return -1;
		char c;
		if (strm >> c) return 1;
		return 0;
	}
	void make_dir(const std::string path) const{
		std::string command = "mkdir " + path;
		int ret_value = system(command.c_str());
	}
	Html get_url(Url url, std::ofstream &log_strm) const;
	void save_load(std::ofstream &log_strm);
public:
	int crawl();
	double get_time_used() const;
	void extract_url(const Html &my_html, const Url &referer, std::vector<Url> &target) const;
	void extract_url(const Url &current_url, const std::string savepath, std::vector<Url> &target) const;
	Crawler(
		Url root_url_,
		std::string save_file_folder_,
		std::string save_log_path_
	) : download_path(save_file_folder_),
		save_file_path(save_log_path_) {
		waiting_urls.push(root_url_);
	}
	Crawler(
		std::string load_log_path_,
		std::string download_path_,
		std::string save_file_path_
	) : save_file_path(save_file_path_),
		download_path(download_path_) {
		std::ifstream load_log_strm;
		load_log_strm.open(load_log_path_);
		if (!load_log_strm) {
			std::cerr << "log file not found" << std::endl;
			exit(0);
		}
		std::string log;
		while (getline(load_log_strm, log)) {
			if (log[0] == 'w') waiting_urls.push(Url(log.substr(2)));
			else visited_urls.insert(Url(log.substr(2)));
		}
	}
	~Crawler() {}

};

#endif