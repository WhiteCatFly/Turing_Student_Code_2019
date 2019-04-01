#include <string>
using std::string;
/*
inline string downloadurllink(string url){
	string order = "curl ";
	order = order.append(url);
	order = order.append(" >> /home/jc");
	return order;
}
*/
string downloadurllink(string url);
string downloadHtml(string strroadadd, int j, string url);
string getCmdResult(const string& strCmd);
string CountFiles(int road);
inline void MakeDir(int road){
	string mk = "mkdir ";
	mk = mk.append(std::to_string(road + 1));
	system(mk.c_str());
}
