#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream> 
using namespace std;
char q[50000][200];
int head,tail,cnt;
bool check(string url)
{
    for (int i=1; i<=tail; i++)
      if (q[i]==url) return 0;

    printf("%s\n",(char*)url.data());

    int l=strlen((char*)url.data());
    for (int i=0; i<=l-12; i++)
    {
       string now="";
       for (int j=i; j<=i+11; j++)
         now=now+url[j];
      if ("download.php"==now)
        return 0;
    }
     for (int i=0; i<=l-4; i++)
    {
       string now="";
       for (int j=i; j<=i+3; j++)
         now=now+url[j];
      if (".php"==now)
        return 1;
    }
    for (int i=0; i<=l-5; i++)
    {
       string now="";
       for (int j=i; j<=i+4; j++)
         now=now+url[j];
      if (".html"==now)
        return 1;
    }
    return 0;
}
void work(string st)
{
  //  printf("%s\n",(char*)st.data());
    int pos;
    for (int i=0; ; i++)
       if (st[i]=='"')
        {
           pos=i; break;
        }
    string ss="";
    for (int i=pos+1; st[i]!='"'; i++)
       ss+=st[i];
   // printf("%s\n",(char*)ss.data());
    int l=strlen((char*)ss.data());
    if (l>=22)
    {
      string s1="";
      for (int i=0; i<=21; i++) s1+=st[i];
      if (s1=="http://info.ruc.edu.cn")
      {
          if (check(ss))
          {
             tail++; strcpy(q[tail],(char*) ss.data());
          } 
          return;
      }
    }  
    if (l>=4)
    {
      string s1="";
      for (int i=0; i<=3; i++) s1+=st[i];
      if (s1=="http") return;
    } 
    string s1="http://info.ruc.edu.cn/";
    s1+=ss;
    if (check(s1))
    {
        tail++; strcpy(q[tail],(char*) s1.data());
    }
}
string converse(int s)
{
    string st="";
    while (s)
    {
       st=(char)((s % 10)+48)+st;
       s=s/10;
    }
    return st;
}
bool parse(string url)
{
     cnt++;
     string name=converse(cnt);
     string ss="wget "+url+" -O "+name;
     if (system((char*)ss.data())) return 0;   
     std::ifstream fin((char*)name.data());
     char ch;
     while (fin>>ch)
     {
        while (ch!='<') fin>>ch;
        string st="";
        bool f=1;
        bool flag=0;
        while (ch!='>')
        {
           fin>>ch;
           if (f && ch!=' ')
           {
              f=0; 
              if (ch=='a') flag=1;
           }
           
           st+=ch; 
        }
       if (flag) work(st); 
     }
    fin.close();
    return 1;
}
int main()
{
    freopen("webcrawler.out","w",stdout);
    cnt=0;
    head=1; tail=1;
    strcpy(q[1],"http://info.ruc.edu.cn");
    while (head<=tail)
    {
        string url=q[head];
        if (parse(url))
          printf("%s\n",(char*) url.data());
        head++;
    }
 
}
