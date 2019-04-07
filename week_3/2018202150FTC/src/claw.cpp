#include "claw.h"

void spider::bfs()
{
    using namespace std;
    while (tobe.empty() == false)
    {

        cout << "how many tobe" << tobe.size() << endl;
        current = tobe.front();
        cout<<"i am current  "<<current<<endl;
        tobe.pop();
        clawed.insert(current);
        content = get_content(current);

        parse(content, current, urls);
        set<string>::iterator it;
        for (it = urls.begin(); it != urls.end(); it++)
        {
            if (clawed.find(*it) == clawed.end())
            {
                tobe.push(*it);
                clawed.insert(*it); // new change;
            }
        }

    }
}




std::string spider::get_content(const std::string & _current)
{
    string current="\"";
    current+=_current;
    current+="\"";
    static int cnt = 0;
    using namespace std;
    cnt++;
    std::ifstream fin;
    string line;
    string order;
    string content;
    string opn;
    int i = 0;
    string num= StringUtils::int2Str(cnt);
    order = "wget " ;
    order += " -O ";
    order += num;
    order += ".html ";
    order+=current;
    cout << "I am order" << ' ' << order << endl;
    system(order.c_str());
    opn = num;
    opn += ".html";
    ofstream fout;
    ofstream ferr;
    fout.open("website.txt",ios::app);
    ferr.open("errfin.txt",ios::app);
    if(fout.is_open())
        fout<<current<<"   "<<cnt<<endl;
    fin.open(opn);
    if (fin.is_open())
    {
        cout << "I am fin" << ' ' << opn << endl;
        while (getline(fin, line))
            content += line;
    }
    else
    {
        ferr<<"I didn't fin   "<<current<<"  "<<cnt<<endl;
    }
    
    fin.close();

    return content;
}
int spider::get_urls(const std::string & res,std::set<std::string> & urls,std::string & current,int mode)
{
     if(current.find("https://")!=string::npos)
        current=current.substr(8);
    if(current.find("http://")!=string::npos)
        current=res.substr(7);

    using namespace std;
    string revise;
     vector <string> fliter{"pdf","ppt","rar","doc","xls","css","rss","gif","jpg","JPG","zip"};
     vector<string>::iterator itf;
     if(res==root ||res=="http://"+root || res=="https://"+root || res=="/")//fliter itself
        return 0;
     if(0 || (res.find("http")!=string::npos && res.find(root)==string::npos))// fliter the outside web
        return 0;
    for(itf=fliter.begin();itf!=fliter.end();itf++)// fliter the wrong format
        if(res.find(*itf)!=string::npos)
            return 0;

    if(res=="/en")//deal with the english version
    {
        urls.insert("econ.ruc.edu.cn/en/index_en.php");
        return 0;
    }
    if(res[0]=='.' && res[1]=='/')
        {
        revise=current;
        char temp[100]="\0";
        int i;
        for(i=2;i<res.size();i++)
           temp[i-2]=res[i];
        temp[i-2]='\0';
        for(i=revise.size()-1;i>=0;i--)
            if(revise[i]!='/')
                revise.erase(i);
            else
                {
                  break;
                }
            revise+=temp;
        urls.insert(revise);
        cout<<"after processed  "<<revise<<endl;
        return 0;
        }
    if( res[0]=='.' && res[1]=='.'&&res[2]=='/')
    {
        revise=current;
        char temp[100];
        int i=revise.size();
        int firstslash=0;
        i--;
         for(;i>=0;i--)
            if(revise[i]!='/')
                revise.erase(i);
            else
                {
                    if(firstslash)
                        break;
                    firstslash++;
                  
                }
        for(i=3;i<res.size();i++)
           temp[i-3]=res[i];
        temp[i-3]='\0';
         if(revise[revise.size()-1]=='/')
            revise+=temp;
        else if(revise[revise.size()-1]!='/')
            revise=revise+"/"+temp;
        urls.insert(revise);
        cout<<"after processed  "<<revise<<endl;
        return 0;

    }
        if (res.find(root) != string::npos )//completed website
        {
            revise=res;
            if(revise.find("http://")!=string::npos)
                revise=revise.substr(7);
            if(revise.find("https://")!=string::npos)
                revise=revise.substr(8);
            urls.insert(revise);
            cout<<"after processed  "<<revise<<endl;
            return 0;
            
        }
        if (res[0] == '/')
        {
            revise = root + res;
            urls.insert(revise);
             cout<<"after processed  "<<revise<<endl;
             return 0;
        }
        else 
        {
            if(current.find('/')==string::npos)
            {
                revise=root+"/"+res;
            }
            else 
            {
                revise=current;
                int i=revise.size();
                i--;
                for(;i>=0;i--)
                    if(revise[i]!='/')
                        revise.erase(i);
                    else
                    {
                        break;
                    }
                revise+=res;
            }
            urls.insert(revise);
             cout<<"after processed  "<<revise<<endl;
             return 0;
            
        }

}



void spider:: parse(std::string & content, std::string& current,std::set<std::string> & urls)
{
    
    using namespace std;
    regex regu("href=[\'\"]*([a-z0-9A-Z_:\\/.\\?=&]+)[\'\"]*");
    regex reguplus("window.location.href=\"([0-9a-zA-Z_:\\/.\\?=&]+)\"");
    smatch res;
    smatch resplus;
    while (regex_search(content, res, regu))
    {
        get_urls(res[1].str(),urls,current,1);
        content=res.suffix();
        continue;
    }   
    while(regex_search(content,resplus,reguplus))
    {
        get_urls(resplus[1].str(),urls,current,2);
        content=res.suffix();
        continue;

    }
}

std::string StringUtils::double2Str(double d){
    string res = "";
    stringstream ss;
    ss << d;
    ss >> res;
    return res;
}

string StringUtils::int2Str(int i){
    string res = "";
    stringstream ss;
    ss << i;
    ss >> res;
    return res;
}

double StringUtils::str2Double(const string &s){
    stringstream ss;
    ss << s;
    double d = 0;
    ss >> d;
    return d;
}


int StringUtils::str2Int(const string &s){
    stringstream ss;
    ss << s;
    int i = 0;
    ss >> i;
    return i;
}