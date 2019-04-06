#include "crawler.h"

string crawler::get_source_code(const string &webname) const
{
	string comm = "wget -q ";
	comm.append("\"");
	comm.append(webname);
	comm.append("\"");
	comm.append(" -O ");
	comm.append(this->storename);
	system(comm.c_str());
	ofstream fp2("crawler.out");
	fp2 << webname << endl;
	ifstream fp(this->storename.c_str());
	if (!fp)
		return "";
	string source_code;
	char temp[this->MAX_STR] = {0};
	while (fp.getline(temp, this->MAX_STR)) {
		source_code.append(string(temp));
		memset(temp, 0, sizeof(temp));
	}
	return source_code;
}
