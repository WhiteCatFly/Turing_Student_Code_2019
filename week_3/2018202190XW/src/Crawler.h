#ifndef CRAWL_H_INCLUDED
#define CRAWL_H_INCLUDED

class Crawler {
private:
	timeval start_time;
	const std::string domain, save_file_folder;
	const Url root_url;
	void set_start_time();
	void make_dir(const std::string path) const{
		std::string command = "mkdir " + path;
		int ret_value = system(command.c_str());
	}
public:
	int crawl();
	double get_time_used() const;
	void extract_url(const Url &current_url, const std::string savepath, std::vector<Url> &target) const;
	Crawler(
		std::string domain_,
		Url root_url_,
		std::string save_file_folder_
	) : domain(domain_), 
		root_url(root_url_), 
		save_file_folder(save_file_folder_)
	{}
	~Crawler() {}

};

#endif