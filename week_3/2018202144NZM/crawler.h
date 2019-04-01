#include <bits/stdc++.h>
using namespace std;

class crawler
{
	private:
		string start_name, storename;
		void normalize_url(string &url_name, string::size_type &index, const string &source_code, const string &web_name, const string &root_name);
		string get_source_code(const string &webname) const;
		enum {
			MAX_STR = 1024
		};
	public:
		crawler();
		crawler(string str, string storename);
		~crawler();
		void _get_url();
};
