
#include "work.h"


inline void work::judge_slash()          //删除多余的slash
{
    char slash = '/';
    
     
    std::string::iterator it;             
	for (it = str.begin(); it != str.end() + 1; it++)
	{
		if (*it == slash && *(it+1) == slash)
          {
            str.erase(it);       
            break;
        
          }		
	}

     urls_tobe_judged.insert(str);

    return;
}

inline void work::judge_mark()          //删除多余的引号
{
    if(str[0] == '\'' || str[0] == '\"')
    {
        str = str.substr(1,str.size());
        str = str.substr(0,str.size()-1);
    }
    
    return;
}

void work::judge(std::string str_,int jump_mark)       //根据jump_mark处理parse结果
{
    str = str_ ;
    judge_mark();
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
        

      std::string :: size_type if_find_root_ = str.find(root_);

      if(if_find_root_ != std::string::npos)
      { 
        //fout.close();
          str = str.substr(sub_root1.size());
          judge_slash();
         // urls_tobe_judged.insert(str);
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
          judge_slash();
          //urls_tobe_judged.insert(str);
       }
       //else if(str[0] == '#')
       //{
       //    return;
       //}
       else if(str[0] == '.')
       {
           if(str[1] == '/')
           {
            char slash = '/';
            str = str.substr(1);
            std::string :: size_type if_find_slash = current.find_last_of(slash);
            std::string sub_current = current.substr(0,if_find_slash);

            str = sub_current + str;
            judge_slash();
            //urls_tobe_judged.insert(str);
            }
            else if(str[1] == '.'&&str[2] == '/')
            {
                 char slash = '/';
                 std::string :: size_type if_find_slash = current.find_last_of(slash);
                 std::string sub_current = current.substr(0,if_find_slash);

                 if_find_slash = sub_current.find_last_of(slash);
                 sub_current = sub_current.substr(0,if_find_slash+1);
                 str = str.substr(3);
                 str = sub_current + str;
              //cout<<str<<endl;
                 judge_slash();
                 //urls_tobe_judged.insert(str);
            }
           
       }
       else
       {   
           if(jump_mark)
           {
               char slash = '/';
               current = current + slash;
               str = current + str;
               judge_slash();
               //urls_tobe_judged.insert(str);
           }
           else
           {
               char slash = '/';
               std::string :: size_type if_find_slash = current.find_last_of(slash);
               if(if_find_slash == std::string::npos)
             {   
               str = slash + str;
               str = root  + str;
               //str="info.ruc.edu.cn/"+str;
               //cout<<str<<endl;
               judge_slash();
               //urls_tobe_judged.insert(str);
             }
               else
             {
              std::string sub_current = current.substr(0,if_find_slash + 1);
              str = sub_current + str;
              //cout<<str<<endl;
              judge_slash();
              //urls_tobe_judged.insert(str);

              }
           }
           
           
           
          
       }
        
        
    }
    

}

