#include"head.h"
using namespace std;

Base::Base()
{
    n=0;
    root="info.ruc.edu.cn";
}

Base::Base(string root_)
{
    n=0;
    root=root_;
}

Base::~Base()
{
    cout<<"DONE!"<<endl;
}

int Base::adjust(string &url)
{
    string ban[100] = {
     ".org", "comsenz", "discuz", "bbs", "rdjjlt", ".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", "bmp",".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", "#", ".zip", ".ppt", "javascript",".7z", ".rar", ".CSS", ".DOC", ".DOCX", "mailto", ".XLS", ".XLSX", ".TXT", ".JPG", ".PNG", "BMP", "rar", "@163",".JPEG", "file://", ".FLV", ".MP4", ".AVI", "@RUC.EUD.CN", ".PDF", ".ZIP", ".7Z", ".RAR", "ebook","END"};
    for (int i = 0; ban[i] != "END"; i++)
    {
        if (url.find(ban[i]) != url.npos)
        {
            //cout<<"find ban "<<ban[i]<<endl;
            return 0;
        }    
    }

    if (url[0] == '\'' || url[0] == '\"') //删除多余的引号
    {
        int n = url.length();
        url.erase(n - 1, 1);
        url.erase(0, 1);
    }

    string root1 = "http://";
    string root2 = "https://";
    if (url.find(root1) != url.npos)//http://
    {
        //cout<<"find http"<<endl;
        if(url.find(root)==url.npos)
            return 0;
        //http://+root+
        int p = url.find(root1+root);
        url.erase(p, root1.length()+root.length());
        return 1;
    }
    if (url.find(root2) != url.npos)
    {
        //cout<<"find https"<<endl;
        if(url.find(root)==url.npos)
            return 0;
        //http://+root+
        int p = url.find(root2+root);
        url.erase(p, root2.length()+root.length());
        return 1;
    }

    if (url[0] != '/')
    {
        string temp = current;
        int len = temp.length();
        if (temp.rfind('/') != temp.npos)//需要更换当前目录
        {
            while (temp[len - 1] != '/')
            {
                temp.erase(len - 1);
                len--;
            }
            url = temp + url;
            int p = url.find(root);
            url.erase(p,root.length());
            return 2;
        }
        else
        {
            url=temp+'/'+url;
            int p=url.find(root);
            url.erase(p,root.length());
            return 3;
        }
    }
    else
    {
        url=current+url;
        int p=url.find(root);
        url.erase(p,url.length());
        return 4;
    }    
}

void Base::parse(string &content,set<string>& urls)
{
    cout<<1<<endl;
    regex pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    smatch s;
    //int num=0;
    while (regex_search(content, s, pattern))
    {
        //num++;
        //cout<<num<<endl;
        string a_url = s[2].str();
        content = s.suffix();
        
        /*cout<<a_url<<endl;
        int x=adjust(a_url);
        cout<<x<<' ';
        cout<<a_url<<endl;*/
        if (adjust(a_url))
            urls.insert(a_url);
    }
}

void Base::BFS()
{
    cout<<"BFS"<<endl;
    cout<<"root: "<<root<<endl;
    todo.push(root);

    while (!todo.empty())
    {   
        current = todo.front();
        todo.pop();
        
        cout<<"current: "<<current<<endl;
        
        done.insert(current);

        n++;
        string cont;
        if(n>1)
            current=root+current;

        Get g(current);
        g.getcontent(cont,n);
        //cout<<(*cont)<<endl;
        set<string> urls;
        parse(cont, urls);
        /*set<string>::iterator it=urls->begin();
        for( ; it!=urls->end();it++)
        {
            cout<<*it<<endl;
        }*/
        
        //int num=0;
        for (auto x :urls)
        {
            if (done.find(x) == done.end())
            {
                //num++;
                //cout<<num<<" "<<x<<endl;
                todo.push(x);
            }    
        }
    }
}