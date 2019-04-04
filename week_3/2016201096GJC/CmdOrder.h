#include <string>
using std::string;

void DownloadStartHtml(string starturl);
string DownloadUrlLink(string url);
string DownloadHtml(string strroadadd, int j, string url);
string GetCmdResult(const string& strCmd);
string CountFiles(int road);
inline void MakeDir(int road){
	string mk = "mkdir ";
	mk = mk.append(std::to_string(road + 1));
	system(mk.c_str());
}
