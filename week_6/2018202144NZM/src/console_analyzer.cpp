#include "console_analyzer.h"

int string_analyzer(string str)
{
	if (str == "gettitle")
		return 0;
	if (str == "getpassage")
		return 1;
	if (str == "geturl")
		return 2;
	if (str == "-o")
		return 3;
	return -1;
}

void console_analyzer(int argc, char *argv[])
{
	string file_name = "parser.out";
	if (argc < 2) {
		cerr << "unknown website!" << endl;
		return;
	}
	string webname = argv[1];
	for (int i = 2; i < argc; i++) {
		int strno = string_analyzer(argv[i]);
		html_parser hp = html_parser(webname);
		html_parser *p = &hp;
		switch (strno) {
			case 0:
				p->get_title(file_name);
				break;
			case 1:
				p->get_passage(file_name);
				break;
			case 2:
				p->get_url(file_name);
				break;
			case 3:
				if (i + 1 < argc) {
					file_name = argv[i + 1];
					i++;
				}
				else
					cerr << "command -o without a filename!" << endl;
				break;
			case -1:
				cerr << "unknown command!" << endl;
			default:
				break;
		}
	}
}
