#include "Query.h"
#include<cassert>
using namespace std;

Query::Query(const std::string &id_,
             const std::string &name_,
             int gender_,
             const std::string &birthplace_,
             const std::string &birthday_,
             int birthyear_,
             const std::string &lostday_,
             int lostyear_,
             int min_height_,
             int max_height_,
             const std::string &lostplace_,
             const std::vector<bool> &descriptions_,
             const std::string& query_string_){

            id = id_;
            name = name_;
            gender = gender_;
            birthplace = birthplace_;
            birthyear = birthyear_;
            birthday = birthday_;
            lostday = lostday_;
            lostyear = lostyear_;
            min_height = min_height_;
            max_height = max_height_;
            lostplace = lostplace_;
            descriptions = descriptions_;
            query_string = query_string_;
             }

Query::Query(string str, int n):gender(-1), birthyear(-1), lostyear(-1), min_height(-1), max_height(-1),descriptions({})
{
    std::string province[] = {"北京", "天津", "上海", "重庆", "河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南", "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾", "内蒙", "广西", "宁夏", "新疆"};//0-30
    std::string description_base[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22"};//0-22

    string::size_type tag_position=str.find("&tag="),input_position;
    string tag,input;
    if(tag_position==str.npos)
    {
        tag="-1";
        input_position=str.find("&ID=");
        input=str.substr(input_position);
        str.erase(input_position);
    }
    else
    {
        tag=str.substr(tag_position);
        str.erase(tag_position);

        input_position=tag.find("&ID=");
        input=tag.substr(input_position);
        tag.erase(input_position);
    }

    int birthprovince_num,lostprovince_num;
    sscanf(str.c_str(),"gender=%d&birthyear=%d&birthprovince=%d&minheight=%d&lostyear=%d&lostprovince=%d",&this->gender,&this->birthyear,&birthprovince_num,&this->min_height,&this->lostyear,&lostprovince_num);
    if(birthprovince_num==-1)
        this->birthplace="";
    else
        this->birthplace=province[birthprovince_num];
    if(lostprovince_num==-1)
        this->lostplace="";
    else
        this->lostplace=province[lostprovince_num];
    if(min_height==-1)
        this->max_height=-1;
    else
        this->max_height=min_height+9;


    if(tag.find("-1")==tag.npos)//have tags
    {
        for(int i=0;i<23;i++)
        {
            if(tag.find(description_base[i])==tag.npos)// no such tag
                descriptions.push_back(0);
            else
                descriptions.push_back(1);
        }
    }
    else
    {
        for(int i=0;i<23;i++)
            descriptions.push_back(0);
    }

    string::size_type id_posi=0,name_posi,search_posi;
    name_posi=input.find("&NAME=");
    search_posi=input.find("&search=");
    this->id=input.substr(4,name_posi-4);
    this->name=input.substr(name_posi+6,(search_posi-name_posi-6));
    this->name=UrlDecode(name);
    string temp(input.substr(search_posi+8));
    this->query_string=UrlDecode(temp);
}

unsigned char Query::ToHex(unsigned char x)  
{  
  return x > 9 ? x + 55 : x + 48;  
} 
 
unsigned char Query::FromHex(unsigned char x)  
{  
  unsigned char y; 
  if (x >= 'A' && x <= 'Z') y = x - 'A' + 10; 
  else if (x >= 'a' && x <= 'z') y = x - 'a' + 10; 
  else if (x >= '0' && x <= '9') y = x - '0'; 
  else assert(0); 
  return y; 
} 
 
std::string Query::UrlEncode(const std::string& str) 
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
 
std::string Query::UrlDecode(const std::string& str) 
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