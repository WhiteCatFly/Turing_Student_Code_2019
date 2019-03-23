#include "spiderWeb.h"

void getUrl(const std::string &filename, const std::string &url){
	using std::string;
	//std::cout << "Downloading " << url << " " << filename << " ";
	string command = "wget --max-redirect=0 --timeout=4 –tries=1 ";
	command += url;
	command += " -O ";
	command += filename;
	std::cout << command << "\n";
	std::system(command.c_str());
	std::cout << "Done\n";
}