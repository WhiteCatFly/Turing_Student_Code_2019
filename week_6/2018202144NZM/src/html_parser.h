#include <bits/stdc++.h>
#include "normal_url.h"

#ifndef HTML_PAR
#define HTML_PAR

using namespace std;

class html_parser {
	protected:
		string source_str, web_name;
		enum {
			MAX_STR = 1000000
		};
	public:
		html_parser();
		html_parser(string input_str);
		html_parser(string file_name, int arg);
		~html_parser();
		string get_source_code(const string &webname);
		virtual void get_title(string file_name);
		virtual void get_passage(string file_name);
		virtual void get_url(string file_name);
};

#endif
