#include "parser.h"

void string_replace(string &content,string &str,string &str_replace)    //将content中的str全部替换为str_replace
{
    std::string::size_type pos = 0;
    std::string::size_type len_str = str.size();
    std::string::size_type len_str_ = str_replace.size();

    while( (pos=content.find(str, pos)) != std::string::npos )
    { 
        content.replace( pos, len_str, str_replace );
        pos += len_str_; 
    }

}

void parser::get_title(string content)
{
    std::string title;
    std::regex pattern("<title>((.*?))</title>", std::regex_constants::icase);
    std::smatch res;
    if (regex_search(content,res,pattern))
    {
        title = res[1].str();
    }

    fout_result << title ;
    fout_result.close();
}
void parser::get_body(string content)
{
    std::regex pattern("<p((.*?))</p>",std::regex_constants::icase);
    std::smatch res;
    std::string blank = "";

    while(regex_search(content,res,pattern))
    {
        std::string text;
        std::string space = " ";
        std::string space_ = "&nbsp;";
 
        text = res[1].str().substr(res[1].str().find_last_of('>')+1,res[1].str().length()-1);
        string_replace(text,space_,space);

        if(text != blank)
        fout_result << text << std::endl;

        content = res.suffix();
    }
  
  fout_result.close();

}
void parser::get_type(string &type,string content)
{
  std::string pattern_ = '<' + type;
  pattern_ = pattern_ + "((.*?))</";
  pattern_ = pattern_ + type + '>';

  std::regex pattern(pattern_,std::regex_constants::icase);
  std::smatch res;
  std::string blank = "";

  while(regex_search(content,res,pattern))
  {
    std::string text;
    std::string space = " ";
    std::string space_ = "&nbsp;";   
 
    text = res[1].str().substr(res[1].str().find_last_of('>')+1,res[1].str().length()-1);
    string_replace(text,space_,space);

    if(text != blank)
    fout_result << text << std::endl;

    content = res.suffix();
    }
  
  fout_result.close();

}
inline void parser::judge_mark(string &str)          //删除多余的引号
{
    if(str[0] == '\'' || str[0] == '\"')
    {
        str = str.substr(1,str.size());
        str = str.substr(0,str.size()-1);
    }
    
    return;
}
inline void parser::judge_jump(string &str)       //windows.location.href中的特殊情况
{
    char slash = '/'; 
    char add = '+';
    string::iterator it; 
    for(it = str.begin() ; it < str.end() ; it ++)
    {
        if(*it == '\"')
            str.erase(it);
        if(*it == '+')
            str.erase(it);
          if(*it == '\"')
            str.erase(it);  
    }
	return;

}
int parser::if_get_urls(std::string str,std::string current,std::string root,std::string &record_str)
{
    judge_mark(str);
    judge_jump(str);

    char slash = '/';
    char dot   = '.';
    const string forbidden_list[]={".css",".js",".jpg",".mp3",".mp4",".png",".zip",".bmp",".ico",
    ".avi", ".ppt",".xls",".doc",".xlsx",".docx",".pptx",".JPG","mailto:","javascript","#","pdf"
    ,"xml","rar","file://"};
    
    for(auto it: forbidden_list)
    {
        string :: size_type if_find_it = str.find(it);

        if(if_find_it != string::npos)
        return 0;

    }

    const string sub_root1 = "http://";
    const string sub_root2 = "https://";
    const string root_     =  sub_root1 + root;

    string :: size_type if_find_subroot1 = str.find(sub_root1);
    string :: size_type if_find_subroot2 = str.find(sub_root2);

    if(if_find_subroot1 != string::npos||if_find_subroot2 != string::npos)   //以http://或https://开头的情况
    { 
        string :: size_type if_find_root_ = str.find(root_);

        if(if_find_root_ != string::npos)    //是站内网址的情况
        { 
            str = str.substr(sub_root1.size());
			record_str = str;
            return 1;
        
        }
      
    }
    else    //以/,./,../,字母开头的情况
    {
        if(str[0] == slash)     //以单个slash开头的情况
        {
            str = root + str;
			record_str = str;
            return 1;
        }
        else if(str[0] == dot)    //以dot开头的情况
        {
            if(str[1] == slash)    //以./开头的情况
            {
                str = str.substr(1);
                string :: size_type if_find_slash = current.find_last_of(slash);
                string sub_current = current.substr(0,if_find_slash);

                str = sub_current + str;
				record_str = str;
                return 1;
            }
            else if(str[1] == dot && str[2] == slash)    //以../开头的情况
            {
                char slash = '/';
                string :: size_type if_find_slash = current.find_last_of(slash);
                string sub_current = current.substr(0,if_find_slash);

                if_find_slash = sub_current.find_last_of(slash);
                sub_current = sub_current.substr(0,if_find_slash+1);
                str = str.substr(3);
                str = sub_current + str;

				record_str = str;
                return 1;
            }
        }
        else    //以字母开头的情况
        {
            string :: size_type if_find_slash = current.find_last_of(slash);
            if(if_find_slash == string::npos)
            {   
                str = slash + str;
                str = root  + str;
				record_str = str;
                return 1;
            }
            else
            {
            	string sub_current = current.substr(0,if_find_slash + 1);
            	str = sub_current + str;
				record_str = str;
            	return 1;
            }
        }
    } 
	return 0;
}
