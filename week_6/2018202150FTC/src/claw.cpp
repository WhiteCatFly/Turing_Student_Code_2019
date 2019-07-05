#include "claw.h"
spiderbase::spiderbase(std::string _root,std::string _path)
{
    
    root=_root;
    path=_path;
    bfs();
    
}
void spider::judge()
{  
    std::ifstream fin_tobe;
    std::ifstream fin_ed;

    std::string record;
    std::string previous_url;
    cnt=0;
    fin_tobe.open("log.txt");
        if(fin_tobe.is_open())
        { 
            std::cout<<"there is a breakpoint";
            fin_ed.open("website.txt");
            while(getline(fin_ed,record)){
                std::stringstream ss;
                ss<<record;
                ss>>previous_url;
                ss.clear();
                clawed.insert(previous_url);
            }
            while(getline(fin_tobe,previous_url)){
                if(clawed.find(previous_url)!=clawed.end())
                    cnt++;
                else 
                    tobe.push(previous_url);
            }
        }
        else
        {
            std::cout<<"there is no breakpoint";
            tobe.push(root);  
        } 
    

}
void spiderbase::bfs()
{
    while (tobe.empty() == false)
    {
        std::cout << "how many tobe" << tobe.size() <<std:: endl;
        current = tobe.front();
        std::cout<<"i am current  "<<current<<std::endl;
        tobe.pop();
        clawed.insert(current);
        content = get_content(current);
        parse(content, current, urls);
        std::set<std::string>::iterator set_it; 
        for (set_it = urls.begin(); set_it != urls.end();set_it++)
        {
            if (clawed.find(*set_it) == clawed.end())
            {
                tobe.push(*set_it);
                clawed.insert(*set_it); // new change;
            }
        }
        urls.empty();    
    }    
}
void spider::bfs()
{
    std::cout<<"enter bfs"<<std::endl;
    judge();
    //to judge if there is a breakpoint
    std::ofstream fout;
    while (tobe.empty() == false)
    {
        std::cout << "how many tobe" << tobe.size() <<std:: endl;
        current = tobe.front();
        std::cout<<"i am current  "<<current<<std::endl;
        tobe.pop();
        clawed.insert(current);
        content = get_content(current);
        parse(content, current, urls);
        std::set<std::string>::iterator set_it; 
        for (set_it = urls.begin(); set_it != urls.end();set_it++)
        {
            if (clawed.find(*set_it) == clawed.end())
            {
                tobe.push(*set_it);
                clawed.insert(*set_it); // new change;
                fout.open("breakpoint.txt",std::ios::app);
                fout<<*set_it<<std::endl;
                fout.close();
            }
        }
        urls.empty();    
    }
}




std::string spiderbase::get_content(const std::string & _current)
{
    std::string current;
    current+=_current;
    cnt++;
    std::ifstream fin;
    std::string line;
    std::string order;
    std::string content;
    std::string opn;
    int i = 0;
    std::string num= StringUtils::int2Str(cnt);
    order = "wget " ;
    order += " -O ";
    if(path!="now")
        order=order+path+"//";
    order += num;
    order += ".html ";
    order += "\"";
    order+=current;
    order+="\"";
    order+=" -c";
    std::cout << "I am order" << ' ' << order <<std:: endl;
    system(order.c_str());
    if(path!="now")
        opn=path+"//";
    opn += num;
    opn += ".html";
    std::ofstream fout;
    std::ofstream ferr;
    fout.open("website.txt",std::ios::app);
    ferr.open("errfin.txt",std::ios::app);
    if(fout.is_open())
        fout<<current<<"   "<<cnt<<std::endl;
    fin.open(opn);
    if (fin.is_open())
    {
        std::cout << "I am fin" << ' ' << opn <<std::endl;
        while (getline(fin, line))
            content += line;
        
    }
    
    else
    {
        ferr<<"I didn't fin   "<<current<<"  "<<cnt<<std::endl;
    }
    
    fin.close();

    return content;
}
std::string spiderbase::process_url_type1(const std::string & res,const std::string & current)
{
    std::string current_copy=current;
    for(int i=current_copy.size()-1;i>=0;i--)
    {
        if(current_copy[i]!='/')
            current_copy.erase(i);
        else
            break;
    }
    std::string after_process=current_copy+res.substr(2);
    return after_process;
}
std::string spiderbase::process_url_type2(const std::string & res,const std::string & current)
{
    std::string after_process;
    std::string current_copy=current;
    int firstslash=0;
    for(int i=current_copy.size()-1;i>=0;i--)
        if(current_copy[i]!='/')
                current_copy.erase(i);
        else
        {
            if(firstslash)
                break;
            firstslash++;         
        }
    after_process=current_copy+res.substr(3);
    return after_process;
}
std::string spiderbase::process_url_type3(const std::string & res,const std::string & current)
{
    std::string after_process;
    if(current.find('/')==std::string::npos)
    {
        after_process=root+"/"+res;
    }
    else 
    {
        after_process=current;
        int i=after_process.size();
        i--;
        for(;i>=0;i--)
            if(after_process[i]!='/')
                after_process.erase(i);
            else
                break;
         after_process+=res;
    }
    return after_process;
}
int spiderbase::category_urls(const std::string & res,std::set<std::string> & urls,std::string & current,int mode)
{
    std::string revise;
    std::vector <std::string> fliter{"javas","pdf","ppt","rar","doc","xls","css","rss","gif","jpg","JPG","zip"};
    std::vector<std::string>::iterator itf;
    if(res==root  || res=="/")//fliter itself
        return 0;
    if(res.find("http")!=std::string::npos && res.find(root)==std::string::npos)// fliter the outside web
        return 0;
    for(itf=fliter.begin();itf!=fliter.end();itf++)// fliter the wrong format
        if(res.find(*itf)!=std::string::npos)
            return 0;
    if(res[0]=='.' && res[1]=='/')
    {
        revise=process_url_type1(res,current);
        urls.insert(revise);
        std::cout<<"after processed  "<<revise<<std::endl;
        return 0;
    }
    if( res[0]=='.' && res[1]=='.'&&res[2]=='/')
    {
        revise=process_url_type2(res,current);
        urls.insert(revise);
        std::cout<<"after processed  "<<revise<<std::endl;
        return 0;
    }
    if (res.find(root) != std::string::npos )//completed website
   {
        revise=res;
        if(revise.find("http://")!=std::string::npos)
            revise=revise.substr(7);
        else if(revise.find("https://")!=std::string::npos)
            revise=revise.substr(8);
        urls.insert(revise);
        std::cout<<"after processed  "<<revise<<std::endl;
        return 0;            
    }
    if (res[0] == '/')
    {
        revise = root + res;
        urls.insert(revise);
         std::cout<<"after processed  "<<revise<<std::endl;
         return 0;
    }
    else 
    { 
        revise=process_url_type3(res,current);
        urls.insert(revise);
        std::cout<<"after processed  "<<revise<<std::endl;
         return 0;      
    }

}



void spiderbase:: parse(std::string & content, std::string& current,std::set<std::string> & urls)
{
    std::regex regu("href=[\'\"]*([a-z0-9A-Z_:\\/.\\?=&]+)[\'\"]*");
    std::regex reguplus("window.location.href=\"([0-9a-zA-Z_:\\/.\\?=&]+)\"");
    std::smatch res;
    std::smatch resplus;
    while (regex_search(content, res, regu))
    {
        category_urls(res[1].str(),urls,current,1);
        content=res.suffix();
        continue;
    }   
    while(regex_search(content,resplus,reguplus))
    {
        category_urls(resplus[1].str(),urls,current,2);
        content=res.suffix();
        continue;

    }
}

std::string StringUtils::double2Str(double d){
    std::string res = "";
    std::stringstream ss;
    ss << d;
    ss >> res;
    return res;
}

std::string StringUtils::int2Str(int i){
    std::string res = "";
    std::stringstream ss;
    ss << i;
    ss >> res;
    return res;
}

double StringUtils::str2Double(const std::string &s){
    std::stringstream ss;
    ss << s;
    double d = 0;
    ss >> d;
    return d;
}


int StringUtils::str2Int(const std::string &s){
    std::stringstream ss;
    ss << s;
    int i = 0;
    ss >> i;
    return i;
}