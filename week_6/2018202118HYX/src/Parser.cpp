#include"head.h"
using namespace std;

Parser::Parser()
{
    target="info.ruc.edu.cn";
    file="file.html";
}

Parser::Parser(string target_)
{
    target=target_;
    file="file.html";
}

Parser::~Parser() {    }

void Parser::getcontent()
{
    string order = "wget --tries=3 --timeout=5s -O " + file + "  " + '\"' + target + '\"';
    system(order.c_str());
}

void Parser::extract_title()
{
    getcontent();
    cout<<"title"<<endl;
    ifstream fin;
    fin.open(file.c_str());
    string line;
    while (getline(fin, line))
    {
        if(line.find("<title>")!=line.npos)
        {  
            while(line[0]!='>')
                line.erase(0,1);
            line.erase(0,1);
            
            int len=line.length();
            while(line[len-1]!='<')
            {
                line.erase(len-1,1);
                len--;
            }
            line.erase(len-1,1);
            
            cout<<line<<endl;
            break;
        }
    }
    fin.close();
}

void Parser::extract_content()
{
    getcontent();
    cout<<"content"<<endl;
    ifstream fin;
    fin.open(file.c_str());
    string line;
    bool m=0;
    while (getline(fin, line))
    {
        if(line.find("</body>")!=line.npos)
        {
            m=0;
            int p=line.find("</body>");
            line.erase(p,line.length()-p-7);
            cout<<line<<endl;
        }
        if(line.find("<body")!=line.npos)
        {  
            m=1;
            int p=line.find("<body");
            line.erase(0,p);
        }
        if(m==1)
            cout<<line<<endl;
    }
    fin.close();
}

void Parser::extract_url()
{
    getcontent();
    cout<<"url"<<endl;
    ifstream fin;
    fin.open(file);
    string line;
    this->content.clear();
    while (getline(fin, line))
        this->content += line;
    //cout<<content<<endl;
    fin.close();

    regex pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    smatch s;
    while (regex_search(content, s, pattern))
    {
        //cout<<"regex_search"<<endl;
        string result = s[2].str();
        content = s.suffix();

        result.erase(0, 1);
        result.erase(result.length() - 1, 1);

        bool m=0;
        string ban[] = {".com", ".org", ".ru","comsenz", "discuz", "bbs", "rdjjlt", ".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", "bmp",".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", "#", ".zip", ".ppt", "javascript",".7z", ".rar", ".CSS", ".DOC", ".DOCX", "mailto", ".XLS", ".XLSX", ".TXT", ".JPG", ".PNG", "BMP", "rar", "@163",".JPEG", "file://", ".FLV", ".MP4", ".AVI", "@RUC.EUD.CN", ".PDF", ".ZIP", ".7Z", ".RAR", "END"};
        for (int i = 0; ban[i] != "END"; i++)
        {
            if (result.find(ban[i]) != result.npos)
                m=1;
        }
        if(m==1)
            continue;
        
        if(result.find("http://")!=result.npos || result.find("https://")!=result.npos)
            cout << result << endl;
        else
        {
            string root=this->target;
            int len=root.length();
            if(result[0]!='/' && root.rfind('/')!=root.npos)
            {
                while(root[len-1]!='/')
                {
                    root.erase(len-1,1);
                    len--;
                }
            }
            
            if(result[0]=='/')
                result="http://"+root+result;
            else
                result="http://"+root+'/'+result;
            
            cout<<result<<endl;
        }
    }
}