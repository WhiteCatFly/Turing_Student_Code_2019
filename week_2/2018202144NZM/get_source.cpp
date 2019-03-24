#include "get_source.h"

string get_source_code(string webname)
{
	string comm = "wget -q ";
	comm.append("\"");
	comm.append(webname);
	comm.append("\"");
	comm.append(" -O ");
	comm.append(storename);
	system(comm.c_str());
	ofstream fp2("crawler.out");
	fp2 << webname << endl;
	ifstream fp(storename.c_str());
	if (!fp)
		return "";
	string source_code;
	char temp[MAX_STR] = {0};
	while (fp.getline(temp, MAX_STR)) {
		source_code.append(string(temp));
		memset(temp, 0, sizeof(temp));
	}
	return source_code;
}
