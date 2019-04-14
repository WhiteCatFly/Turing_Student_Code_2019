#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <sys/time.h>

#include "Url.h"
#include "TagNode.h"
#include "Html.h"

int main(int argc, char *argv[]) {
	Html my_html;
	if (argc == 2 && strcmp(argv[1], "-h") == 0) {
		std::cout << "-f <file_name>" << std::endl;
		std::cout << "-u <url> <save_file_folder>" << std::endl;
		return 0;
	}
	else if (argc == 3 && strcmp(argv[1], "-f") == 0) {
		my_html = Html(argv[2]);
	}
	else if (argc == 4 && strcmp(argv[1], "-u") == 0) {
		my_html = Html(Url(argv[2]), argv[3]);
	}
	my_html.print();
	std::cout << "what do you want to do next?" << std::endl;
	std::cout << "1.parse title 2.parse text 3.parse href 4.print 5.exit" << std::endl;
	int option;
	std::cin >> option;
	while (!(option >= 1 && option <= 5)) {
		std::cout << "invalid option: " << option << std::endl;
		std::cout << "input again" << std::endl;
		std::cin >> option;
	}
	while (option != 5) {
		switch (option)	{
			case 1:
				my_html.parse_title();
				break;
			case 2:
				my_html.parse_text();
				break;
			case 3:
				my_html.parse_href();
				break;
			case 4:
				my_html.print();
				break;
			default:
				break;
		}
		std::cout << "what do you want to do next?" << std::endl;
		std::cout << "1.parse title 2.parse text 3.parse href 4.print 5.exit" << std::endl;
		std::cin >> option;
		while (!(option >= 1 && option <= 5)) {
			std::cout << "invalid option: " << option << std::endl;
			std::cout << "input again" << std::endl;
			std::cin >> option;
		}
	}
	return 0;
}