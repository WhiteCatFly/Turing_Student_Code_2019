#ifndef HTML_PAR
#include "html_parser.h"
#endif

#ifndef D_PAR
#define D_PAR

class title_parser:public html_parser {
	void get_title(string file_name);
};

class passage_parser:public html_parser {
	void get_passage(string file_name);
};

class url_parser:public html_parser {
	void get_url(string file_name);
};

#endif
