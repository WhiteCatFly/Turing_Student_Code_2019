#include "head.h"

using namespace std;

int crawl::adjust(string &a_url)
{
    if (a_url[0] == '\'' || a_url[0] == '\"') //删除多余的引号
    {
        int n = a_url.length();
        a_url.erase(n - 1, 1);
        a_url.erase(0, 1);
    }
    
    string root1 = "http://";
    string root2 = "https://";
    if (a_url.find(root1) != a_url.npos)
    {
        int p = a_url.find(root1);
        a_url.erase(p, root1.length());
    }
    if (a_url.find(root2) != a_url.npos)
    {
        int p = a_url.find(root2);
        a_url.erase(p, root2.length());
    }
    
    string ban[100] = {
    ".com", ".org", ".ru","comsenz", "discuz", "bbs", "rdjjlt", ".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", "bmp",".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", "#", ".zip", ".ppt", "javascript",".7z", ".rar", ".CSS", ".DOC", ".DOCX", "mailto", ".XLS", ".XLSX", ".TXT", ".JPG", ".PNG", "BMP", "rar", "@163",".JPEG", "file://", ".FLV", ".MP4", ".AVI", "@RUC.EUD.CN", ".PDF", ".ZIP", ".7Z", ".RAR", "END"};
    for (int i = 0; ban[i] != "END"; i++)
    {
        if (a_url.find(ban[i]) != a_url.npos)
            return 0;
    }
    
    if (a_url[0] != '/')
    {
        string temp = current;
        int len = temp.length();
        if (temp.rfind('/') != temp.npos)
        {
            while (temp[len - 1] != '/')
            {
                temp.erase(len - 1);
                len--;
            }
            a_url = temp + a_url;
        }
    }
    return 1;
}

void crawl::parse(string &content, set<string> &urls)
{
    regex pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    smatch s;
    while (regex_search(content, s, pattern))
    {
        string a_url = s[2].str();
        content = s.suffix();

        //cout<<a_url<<endl;
        
        if (adjust(a_url))
            urls.insert(a_url);
    }
}
