#include "operate.h"

//using namespace std;


void judge( std::string str , std::string &current , std::set<std::string> &urls_tobe_judged )
{
    const std::string forbidden_list[]={".css",".js",".jpg",".mp3",".mp4",".png",".zip",".jpeg",".ico",
    ".avi", ".flv",".xls",".doc",".ppt",".xlsx",".docx",".pptx",".rar","mailto:"};

    for(auto it: forbidden_list)
    {
        std::string :: size_type if_find_it = str.find(it);

        if(if_find_it != std::string::npos)
        return;

    }
    
    const std::string sub_root1 = "http://";
    const std::string sub_root2 = "https://";
    const std::string root_     = root + sub_root1;

    std::string :: size_type if_find_subroot1 = str.find(sub_root1);
    std::string :: size_type if_find_subroot2 = str.find(sub_root2);

    if(if_find_subroot1 != std::string::npos||if_find_subroot2 != std::string::npos)
    { 
      std::string :: size_type if_find_root_ = str.find(root_);

      if(if_find_root_ != std::string::npos)
      {  
          str = str.substr(sub_root1.size());
          //cout<<str<<endl;
          urls_tobe_judged.insert(str);
      }
      
    }
    else
    {
       if(str[0] == '/') 
       {
          str = root + str;
          //cout<<str<<endl;
          urls_tobe_judged.insert(str);
       }
       else if(str[0] == '#')
       {
           return;
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
               urls_tobe_judged.insert(str);
           }
           else
           {
              std::string w = current.substr(0,if_find_slash + 1);
              str = w + str;
              //cout<<str<<endl;
              urls_tobe_judged.insert(str);

           }
           
          
       }
        
        
    }
    

}

extern int total_urls;

std::string getcontent( std::string &current, int &total_urls , std::string &storage_path)
{   
   

    std::ifstream fin;

    total_urls++;
    std::cout << total_urls << std::endl;
    
    std::string content;
    std::string line;

    std::string order = "wget --timeout=3 --waitretry=0 --tries=5 \"";
    std::string opn   = "\" -O ";
    //std::string file  = "/home/halcyon/index.html";
    
    opn   += storage_path;
    order += current;
     
    order += opn;
    //cout<< order <<endl;
    system (order.c_str());

    fin.open(storage_path);
    //cout<<fin.is_open(opn)<<endl;
    while (getline(fin,line))
        content += line;

    fin.close();

    return content;
}

void parse ( std::string &content , std::string &current , std::set <std::string> &urls_tobe_judged )
{
    //using namespace std;

    std::regex  pattern("<a href=\"((.*?))\"");
    std::smatch res;
    
    while(regex_search(content,res,pattern))
    {   
       
        //cout<< a[0].str() <<endl;
        judge(res[1].str(),current,urls_tobe_judged);
        //cout<< a[1].str() <<endl;
        
        content = res.suffix();
        
    }
}

