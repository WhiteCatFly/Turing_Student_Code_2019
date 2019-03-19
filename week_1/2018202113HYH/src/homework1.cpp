#include <algorithm>
#include <vector>
#include <regex>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <time.h>

using namespace std;

string root = "info.ruc.edu.cn";

queue <string> tobe;
  set <string> clawed;
  set <string> urls;

int total = 0;

ifstream fin;

void judge(string str,string current)
{
    string rt = "http://info.ruc.edu.cn";
    string r1 = "http://";
    string r2 = "https://";
    string :: size_type i1 = str.find(r1);
    string :: size_type i2 = str.find(r2);
    if(i1 != string::npos||i2 != string::npos)
    { 
      string :: size_type i3 = str.find(rt);
      if(i3!=string::npos)
      {  
          str=str.substr(7);
          //cout<<str<<endl;
          urls.insert(str);
      }
      
    }
    else
    {
       if(str[0]=='/') 
       {
          str="info.ruc.edu.cn"+str;
          //cout<<str<<endl;
          urls.insert(str);
       }
       else if(str[0]=='#')
       {
           return;
       }
       else
       {
           char ok = '/';
           string :: size_type i = current.find_last_of(ok);
           if(i==string::npos)
           {
               str="info.ruc.edu.cn/"+str;
               //cout<<str<<endl;
               urls.insert(str);
           }
           else
           {
              string w=current.substr(0,i+1);
              str=w+str;
              //cout<<str<<endl;
              urls.insert(str);
           }
           
          
       }
        
        
    }
    

}
string getcontent(string current)
{
    total++;
    cout<< total <<endl;
    //cout<<"看我看我！！！！"<<endl;
   
    string line;
    string order = "wget --timeout=3 --waitretry=0 --tries=5 \"";
    string content;
    string opn = "\" -O /home/halcyon/index.html";
    string file = "/home/halcyon/index.html";
    
    order += current;
     
    order = order + opn;
    //cout<< order <<endl;
    
    system (order.c_str());
    fin.open(file);
    //cout<<fin.is_open(opn)<<endl;
    while (getline(fin,line))
        content += line;

    fin.close();
    return content;
}

void parse (string content,string current)
{
    regex pattern("<a href=\"((.*?))\"");
    smatch a;
    while(regex_search(content,a,pattern))
    {   
       
        //cout<< a[0].str() <<endl;
      
        judge(a[1].str(),current);
        //cout<< a[1].str() <<endl;
        //urls.insert(a[1].str());
        content = a.suffix();
        
    }
}

int main()
{
     clock_t start,finish;
     start = clock();
     tobe.push(root);
     while (!tobe.empty() )
     {
         string current = tobe.front();
         tobe.pop();
         string content = getcontent(current);
         clawed.insert(current);
         parse(content,current);
        for(auto it :urls )
        {
            if(clawed.find(it) == clawed.end())
            {
                tobe.push(it);
                clawed.insert(it);
            }
               
        }
     }

     finish = clock();
     double time;
     time = (double)(finish - start) / CLOCKS_PER_SEC;
     cout << "total time :" << time << "seconds" << endl;
     cout << "total urls :" << total << endl;
     return 0;
}