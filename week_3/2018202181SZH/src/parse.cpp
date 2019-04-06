#include"unit.h"
#include<iostream>
#include<regex>
#include<queue>              
#include<string>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;

extern string sensitive_words[100];
void website::parseUrls(string &src,set<string> &store){
    //regex  pattern("href=[\'\"]?([a-z0-9_:\\/.\\?=&]+)[\'\"]?");
    regex  pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    //regex pattern("href=\"((?!http://)(?!http/,/.://)(.*?))\"");
    //regex  jump("window.location.href=\"([a-z0-9_:\\/.]+)\"");
    smatch urls;
    while(regex_search(src,urls,pattern)){
        //store.insert(urls[1].str());
       // cout<<urls[1].str()<<endl;
       string temp = urls[2].str();
       string root1 = "http://";
       string root2 = "https://";

       if(temp.find(root1) != temp.npos){
           int num_te = temp.find(root1);
           temp.erase(num_te,root1.size()); 
       }
        if(temp.find(root2) != temp.npos){
           int num_te = temp.find(root2);
           temp.erase(num_te,root2.size()); 
       }
       if(temp[0] == '\''||temp[0] == '\"')  //删除多余的“ ‘‘ “
       {
           int n = temp.size();
       temp.erase(n-1,1);temp.erase(0,1);
       }
       int flag = 0;
       for(int i = 0; sensitive_words[i] != "words_end"; i++){

           if(temp.find(sensitive_words[i]) != temp.npos){
               flag++;  break;
           }
       }
      // cout<<temp<<endl;
       if(!flag){
           if(temp[0] != '/' ){
           //cout<<current_url<<endl;
           string ref = current_url;
           int nn = ref.size();
           if(ref.find("\\")!=ref.npos){
               while(ref[nn-1] != '/'){
               ref.erase(nn-1);
               nn --;
           }
           temp = ref + temp;
           }
           
       }
    }
       
       /*if(temp.find("../") != temp.npos){
           int n = temp.find("../");
           temp.erase(n,3);
       }*/
       if (!flag)   store.insert(temp);
        src = urls.suffix();
    }
    /*while(regex_search(src,urls,jump)){
        //store.insert(urls[1].str());
       // cout<<urls[1].str()<<endl;
       string temp = urls[1].str();
        if(temp.find("http") != temp.npos){
            temp.erase(0,7);
        }

       int flag = 0;
       for(int i = 0; sensitive_words[i] != "words_end"; i++){
    
           if(temp.find(sensitive_words[i]) != temp.npos){
               flag++;
             break;
           }
       }
       if (!flag)   store.insert(temp);
        src = urls.suffix();
    }*/

}
