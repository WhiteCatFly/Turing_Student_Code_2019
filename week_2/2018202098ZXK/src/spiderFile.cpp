#include "spiderFile.h"
#include <sstream>

std::string load2text(const std::string &filename){
	using namespace std;
	ifstream in(filename);
	if(!in) return "";
	ostringstream tmp;
	tmp << in.rdbuf();
	return tmp.str();;
}