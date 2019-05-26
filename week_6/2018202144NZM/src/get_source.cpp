#include "html_parser.h"

string getTime()
{
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

void print_err_log(string webname)
{
	cout << getTime << "	" << webname << " can't found!";
}

string html_parser::get_source_code(const string &webname)
{
	string comm = "wget -q ";
	string storename = "url_source_code";
	comm.append("\"");
	comm.append(webname);
	comm.append("\"");
	comm.append(" -O ");
	comm.append(storename);
	system(comm.c_str());
	ifstream fp(storename.c_str());
	if (!fp) {
		print_err_log(webname);
		return "";
	}
	string source_code;
	char temp[this->MAX_STR] = {0};
	while (fp.getline(temp, this->MAX_STR)) {
		source_code.append(string(temp));
		memset(temp, 0, sizeof(temp));
	}
	return source_code;
}
