#include "parser.h"



void parser::get_title()
{
    std::regex pattern("<title>((.*?))</title>", std::regex_constants::icase);
    std::smatch res;
    if (regex_search(content,res,pattern))
    {
      title = res[1].str();
    }

    fout << title ;
    fout.close();
}
void parser::get_body()
{
    body = "";
    std::ostringstream oss(std::ios_base::ate);
    oss.str(body);
    
    std::string text_start   = "<p" ;
    std::string text_end     = "</p>" ;
    std::string text_start_  = "<P" ;
    std::string text_end_    = "</P>" ;
    int find_start  = content.find(text_start);
    int find_start_ = content.find(text_start_);
  
    while (find_start != -1 || find_start_ != -1)
    {
        
        std::string text = "";
        int find_end  = content.find(text_end,find_start);
        int find_end_ = content.find(text_end_,find_start_);

       //fout << find_start << std::endl;
       //fout << find_start_ << std::endl;
       
        //int mark_ = 0;
        if((find_start < find_start_ && find_start != -1)|| find_start_ == -1)
        { 
            for (int i = find_start ; i < find_end ; i++)
                text += content[i];

            find_start = content.find(text_start,find_end);

        }
        else
        {
            for (int i = find_start_ ; i < find_end_ ; i++)
                text += content[i];

            
            find_start_ = content.find(text_start_,find_end_);
            
        }
        
    
            if(text.find_last_of('>'))
            text = text.substr(text.find_last_of('>') + 1);

            if(text.size())
            oss << text << std::endl;
     
        
    } 

    fout << oss.str() << std::endl;
    oss.clear();


    fout.close();

}
void parser::get_urls()
{
    std::regex pattern("href=[\'\"]?([\u4e00-\u9fa5a-zA-Z0-9_:\\/.\\?=&]+)[\'\"]?",std::regex_constants::icase);
    std::smatch res;

    while(regex_search(content,res,pattern))
    {   
       
    //cout<< a[0].str() <<endl;
    judge(res[1].str());
    //cout<< a[1].str() <<endl;
        
    content = res.suffix();
        
    }

    for(auto it:urls)
    {
        fout << it << std::endl;
    }

}
void parser::judge_mark(std::string str)
{
    if(str[0] == '\'' || str[0] == '\"')
    {
        str = str.substr(1,str.size());
        str = str.substr(0,str.size()-1);
    }
    
    return;
}

void parser::judge_slash(std::string str)
{
    char slash = '/';
    if(str[str.size()-1] == slash)
    {
      str = str.substr(0,str.size()-1);
    }
    
     
    std::string::iterator it;             
	for (it = str.begin(); it != str.end() + 1; it++)
	{
		if (*it == slash && *(it+1) == slash)
          {
            str.erase(it);       
            break;
        
          }		
	}

    urls.push_back(str);

    return;   
}
void parser::judge(std::string str)
{
    judge_mark(str);

    const std::string forbidden_list[]={".css",".js",".jpg",".mp3",".mp4",".png",".zip",".bmp",".ico",
    ".avi", ".ppt",".xls",".doc",".xlsx",".docx",".pptx",".JPG","mailto:","javascript","#","pdf"
    ,"xml","rar","file://"};

    for(auto it: forbidden_list)
    {
        std::string :: size_type if_find_it = str.find(it);

        if(if_find_it != std::string::npos)
        return;

    }
    
    const std::string sub_root1 = "http://";
    const std::string sub_root2 = "https://";
    const std::string root_     =  sub_root1 + root;

    std::string :: size_type if_find_subroot1 = str.find(sub_root1);
    std::string :: size_type if_find_subroot2 = str.find(sub_root2);

    if(if_find_subroot1 != std::string::npos||if_find_subroot2 != std::string::npos)
    { 
     
      if(if_find_subroot1 != std::string::npos)
      { 
        //fout.close();
          str = str.substr(sub_root1.size());
          judge_slash(str);
         // urls_tobe_judged.insert(str);
      }

      else
      {
         str = str.substr(sub_root2.size());
         judge_slash(str);
      }
      
      
    }
    else
    {
       if(str[0] == '/') 
       {
          if(str.size() == 1)
          return;

          str = root + str;
          //cout<<str<<endl;
          judge_slash(str);
          //urls_tobe_judged.insert(str);
       }
      
       else if(str[0] == '.')
       {
           if(str[1] == '/')
           {
            char slash = '/';
            str = str.substr(1);
            std::string :: size_type if_find_slash = root.find_last_of(slash);
            std::string sub_current = root.substr(0,if_find_slash);

            str = sub_current + str;
            judge_slash(str);
            //urls_tobe_judged.insert(str);
            }
            else if(str[1] == '.'&&str[2] == '/')
            {
                 char slash = '/';
                 std::string :: size_type if_find_slash = root.find_last_of(slash);
                 std::string sub_current = root.substr(0,if_find_slash);

                 if_find_slash = sub_current.find_last_of(slash);
                 sub_current = sub_current.substr(0,if_find_slash+1);
                 str = str.substr(3);
                 str = sub_current + str;
                 //cout<<str<<endl;
                 judge_slash(str);
                 //urls_tobe_judged.insert(str);
            }
           
       }
       else
       {   
               char slash = '/';
               std::string :: size_type if_find_slash = root.find_last_of(slash);
               if(if_find_slash == std::string::npos)
             {   
               str = slash + str;
               str = root  + str;
               //str="info.ruc.edu.cn/"+str;
               //cout<<str<<endl;
               judge_slash(str);
               //urls_tobe_judged.insert(str);
             }
               else
             {
              std::string sub_current = root.substr(0,if_find_slash + 1);
              str = sub_current + str;
              //cout<<str<<endl;
              judge_slash(str);
              //urls_tobe_judged.insert(str);

             }
        
           
           
           
          
       }
        
        
    }
    
}