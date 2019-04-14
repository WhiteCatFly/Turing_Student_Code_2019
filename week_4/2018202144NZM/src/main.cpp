#include "html_parser.h"

int main()
{
	int arg = 0;
	html_parser p = html_parser("source_string");
	html_parser p1 = html_parser("source_file", arg);
	p.get_title("file.out");
	p.get_passage("file.out");
	p.get_url("file.out", "web_name");
	return 0;
}
