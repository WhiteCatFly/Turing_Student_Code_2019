#ifndef SEARCH_ENGINE_INCLUDED
#define SEARCH_ENGINE_INCLUDED

class Page
{
public:
	std::string m_title, m_url;
	std::vector<std::vector<std::string>> m_contents;
	Page() = default;
	Page(const std::string &title, const std::string &url,
		 const std::vector<std::vector<std::string>> &contents):
		m_title(title), m_url(url), m_contents(contents) {};
};

class Search_Result
{
private:
	double m_tf_idf;
	std::string m_title, m_url, m_context;
public:
	Search_Result() = default;
	Search_Result(double tf_idf, const std::string &title,
				  const std::string &url,
				  const std::string &context):
		m_tf_idf(tf_idf), m_title(title),
		m_url(url), m_context(context) {};
	bool operator < (const Search_Result &rhs) const
	{
		return m_tf_idf > rhs.m_tf_idf;
	}
	friend std::ostream & operator << (std::ostream &os, const Search_Result &result);
};

class Search_Engine
{
private:
	std::map<std::string, std::map<int, std::map<int, std::vector<int>>>> m_list;
	std::vector<Page> m_pages;
public:
	Search_Engine() = default;
	Search_Engine(const std::string file_name);
	std::vector<Search_Result> search(const std::string &query);
};

#endif