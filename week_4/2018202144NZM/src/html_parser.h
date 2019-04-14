#include <bits/stdc++.h>
#include "normal_url.h"

using namespace std;

class html_parser {
	protected:
		string source_str;
		enum {
			MAX_STR = 1000000
		};
	public:
		html_parser();
		html_parser(string input_str);
		html_parser(string file_name, int arg);
		~html_parser();
		void get_title(string file_name);
		void get_passage(string file_name);
		void get_url(string file_name, string web_name);
};
