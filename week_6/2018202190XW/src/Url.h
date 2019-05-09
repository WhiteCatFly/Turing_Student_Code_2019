#ifndef URL_PARSER_H_INCLUDED
#define URL_PARSER_H_INCLUDED

class Url {
	private:
		std::string path;
	public:
		void normalize(std::string referer);
		bool empty() const;
		std::string str();
		size_t rfind(const char &c) const;
		std::string substr(size_t from_pos, size_t length) const;
		friend bool operator < (const Url &lhs, const Url &rhs);
		friend bool operator == (const Url &lhs, const Url &rhs);
		std::string get_savepath() const;
		std::string get_path() const{
			return path;
		}
		Url() {}
	Url(std::string url) : path(url) {}
	~Url() {}
};

#endif