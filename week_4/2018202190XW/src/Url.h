#ifndef URL_H_INCLUDED
#define URL_H_INCLUDED

class Url {
private:
	std::string path;
	std::string savepath;
	std::string protocol, host, location, query;
	bool parse_url(std::string url);
	void parse_query();
	void normalize();
	void generate_path();
	void generate_savepath();
public:
	std::string get_protocol() const {
		return protocol;
	}
	std::string get_host() const {
		return host;
	}
	std::string get_path() const {
		return path;
	}
	std::string get_savepath() const{
		return savepath;
	}
	bool empty() const {
		return path.empty();
	}
	size_t find(const std::string &s) const{
		return path.find(s);
	}
	size_t rfind(const char &c) const{
		return path.rfind(c);
	}
	std::string substr(size_t from_pos, size_t length) const{
		return path.substr(from_pos, length);
	}
	friend bool operator < (const Url &lhs, const Url &rhs);
	friend bool operator == (const Url &lhs, const Url &rhs);
	Url() {}
	Url(std::string url);
	Url(std::string url, const Url &referer);
	void normalize(const std::string &domain, const Url &referer_url);
	~Url() {}
};

#endif