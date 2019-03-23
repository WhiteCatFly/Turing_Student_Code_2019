#include "spiderWeb.h"

int getUrl(const std::string &filename, const std::string &url){
	using std::string;
	//std::cout << "Downloading " << url << " " << filename << " ";
	int system_code;
	string command = "wget --max-redirect=0 --timeout=4 –tries=1 ";
	command += url;
	command += " -O ";
	command += filename;
	std::cout << command << "\n";
	system_code = std::system(command.c_str());
	if(system_code == 0){
		std::cout << "Done\n" << std::endl;
	}
	else
		std::cout << "Error in downloading " << url << std::endl;
	return system_code;
}