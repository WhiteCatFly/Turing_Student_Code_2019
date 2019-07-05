#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <vector>
#include "searchengine.h"
using  std::cout;
using std::endl;
using std::vector;
using std::string;
unsigned char ToHex(unsigned char x)  
{  
  return x > 9 ? x + 55 : x + 48;  
} 
 
unsigned char FromHex(unsigned char x)  
{  
  unsigned char y; 
  if (x >= 'A' && x <= 'Z') y = x - 'A' + 10; 
  else if (x >= 'a' && x <= 'z') y = x - 'a' + 10; 
  else if (x >= '0' && x <= '9') y = x - '0'; 
  else assert(0); 
  return y; 
} 
 
std::string UrlEncode(const std::string& str) 
{ 
  std::string strTemp = ""; 
  size_t length = str.length(); 
  for (size_t i = 0; i < length; i++) 
  { 
    if (isalnum((unsigned char)str[i]) ||  
      (str[i] == '-') || 
      (str[i] == '_') ||  
      (str[i] == '.') ||  
      (str[i] == '~')) 
      strTemp += str[i]; 
    else if (str[i] == ' ') 
      strTemp += "+"; 
    else 
    { 
      strTemp += '%'; 
      strTemp += ToHex((unsigned char)str[i] >> 4); 
      strTemp += ToHex((unsigned char)str[i] % 16); 
    } 
  } 
  return strTemp; 
} 
 
std::string UrlDecode(const std::string& str) 
{ 
  std::string strTemp = ""; 
  size_t length = str.length(); 
  for (size_t i = 0; i < length; i++) 
  { 
    if (str[i] == '+') strTemp += ' '; 
    else if (str[i] == '%') 
    { 
      assert(i + 2 < length); 
      unsigned char high = FromHex((unsigned char)str[++i]); 
      unsigned char low = FromHex((unsigned char)str[++i]); 
      strTemp += high*16 + low; 
    } 
    else strTemp += str[i]; 
  } 
  return strTemp; 
}  
int main() {
    cout<<"Content-type:text/html;charset=utf-8\n\n"<<endl<<endl;
    string ans = getenv("QUERY_STRING");
    
    string arr[8] = {"username","gender","age","birthPlace","lostPlace","lostYear","lostHeight","others"};
	for(int i = 0;i < 8;i++){
        
		string temp_std = arr[i];
		int len = temp_std.length();
		int start = ans.find(temp_std);
		int end = ans.find('&',start);
		arr[i] = ans.substr(start+len+1,end-start-len-1);
		
		arr[i] = UrlDecode(arr[i]);
    if(i==2||i==5||i==6){
      if(arr[i]=="")arr[i] = "-1";
    }
	}
	vector<vector<string>>res;
  
  
	SearchEngine excellent;
	
  excellent.Initialize2();
  
  res = excellent.Search(arr);
  
  
	cout<<"<!DOCTYPE html>\n";
    cout<<"<html>\n";
	cout<<"<head>\n";
    cout<<"<title>破镜重圆寻亲网</title>\n";
    cout<<"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
    cout<<"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n";
    cout<<"<meta name=\"keywords\" content=\"SubLime Signup Form web template Responsive, Login form web template,Flat Pricing tables,Flat Drop downs  Sign up Web Templates, Flat Web Templates, Login sign up Responsive web template, SmartPhone Compatible web template, free webdesigns for Nokia, Samsung, LG, SonyEricsson, Motorola web design\" />\n";
    cout<<"<link href=\"../css/style.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />\n";
    cout<<"<link href=\"../css/popuo-box.css\" rel=\"stylesheet\" type=\"text/css\" media=\"all\" />\n";
    
    cout<<"</head>\n";
    cout<<"<body>\n";
    cout<<"<div >\n";
    cout<<"<div class=\"center-container\">\n";
    cout<<"<h1 class=\"agile-head text-center\">\n";
    cout<<"<img src = \"../css/timg.jpg\" width=\"50\" height=\"50\" agile = \"left\"/>";
    cout<<"破镜重圆寻亲网</h1>\n";
    cout<<"<div class=\"container\">\n";
    cout<<"<div class=\"form_w3layouts\">\n";
    cout<<"<div class=\"w3layouts-title\">\n";
    cout<<"<h2 class=\"w3ls-left\">返回结果如下：</h2>\n";
    int num = res.size();
    
    for(int i=0;i<num;i++){
       
        cout<<"<p style=\"text-align:center;font-size:2em;color:rgb(32, 16, 68)\">结果"<<i+1<<"：</p>\n";
         
        for(int j = 0;j < 9;j++){
          if(j==8){
            cout<<"<div style=\"text-align:center\">";
            cout<<"<a  href=\""<<res[i][j]<<"\" target=\"_blank\" style=\"text-align:center\">"<<res[i][j]<<"</a>";
            cout<<"</div>";
            break;
            ;
          }
          cout<<"<p class=\"text-center\">"<<res[i][j]<<"</p>\n";
        }
        
    }
    

    cout<<"<div class=\"clear\"></div>\n";
    cout<<"</div>\n";
    cout<<"</div>	\n";
    cout<<"</div>\n";
    cout<<"<div class=\"agileits-w3layouts-copyright text-center\">\n";
    cout<<"<p>© 2019 &nbsp;高级程设 &nbsp;  丁海鹏 陈洋 思子华小组</p>\n";
    cout<<"</div>	\n";
    cout<<"</div>	\n";
    cout<<"</div>\n";
    cout<<"</body>\n";
    cout<<"</html>\n";
    cout<<"";
    cout<<"";
    cout<<"";
    return 0;
}