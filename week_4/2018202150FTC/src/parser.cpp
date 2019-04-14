
#include"parser.h"
Htmlparser::Htmlparser(std::string name)
{
        source=name;
        mode=1;
        std::cout<<"if you want title, press 1;"<<std::endl;
        std::cout<<"if you want picture press 2;"<<std::endl;
        std::cout<<"if you want urls press 3;"<<std::endl;
        std::cout<<"if you want paragraph press 4;"<<std::endl;
        std::cout<<"if you don't want anymore,press 0"<<std::endl;
        readin();}
void Htmlparser::readin()
{
    if(mode==2)
        interface();
    std::string line;
    std::fstream fin;
    fin.open(source);
    if(fin.is_open())
    {
        std::cout<<"i get in";
        while(getline(fin,line))
            content+=line;
        interface();
    }
    else{
        std::cout<<"fin in error";
    }

}
void Htmlparser::interface()
{
    int choice;
    std::cin>>choice;
    while(choice!=0)
    {
        if(choice==1)
            gettitle();
        if(choice==2)
            getpic();
        if(choice==3)
            geturl();
        if(choice==4)
            getpara();
        std::cin>>choice;
    }

}
void Htmlparser::gettitle()
{
    std::fstream fouttitle;
    fouttitle.open("title.txt",std::ios::app);
    std:: string titbegin1="<title>";
    std::string titend1="</title>";
    std::string titbegin2="<TITLE>";
    std::string titend2="</TITLE>";
    std::string title;
    std::string content_copy=content;
    if(content.find(titbegin1)==std::string::npos && content.find(titbegin2)==std::string::npos)
        fouttitle<<"it has no title at all"<<std::endl;
    else if(content.find(titbegin1)<content.find(titbegin2))
    title=content_copy.substr(content_copy.find(titbegin1)+titbegin1.size(),
        content_copy.find(titend1)-content_copy.find(titbegin1)-titbegin1.size());
    else
    {
        title=content_copy.substr(content_copy.find(titbegin2)+titbegin2.size(),
        content_copy.find(titend2)-content_copy.find(titbegin2)-titbegin2.size());
    }
     fouttitle<<title;
     fouttitle.close();

}
void Htmlparser::geturl()
{
    std::fstream fouturl;
    fouturl.open("url.txt",std::ios::app);
    std::string content_copy=content;
    std::smatch res;
    std::regex regu_href("href=[\'\"]*([a-z0-9A-Z_:\\/.\\?=&]+)[\'\"]*");
    while(regex_search(content_copy,res,regu_href))
    {

        std::vector<std::string> fliter={"rar","JPG","css","jpg","xls","doc","zip"};
        int i;
        for(i=0;i<fliter.size();i++)
            if(res.str().find(fliter[i])!=std::string::npos)
            {
                content_copy=res.suffix();
                continue;
            }
        fouturl<<"a link: "<<res[1].str()<<std::endl;
        content_copy=res.suffix();
    }
    fouturl<<std::endl;
    fouturl.close();

}
void Htmlparser::getpic()
{
    std::fstream foutpic;
    foutpic.open("picture.txt",std::ios::app);
    std::regex regu_pic("src=([\'\"][0-9a-zA-Z:\\/._?=]+)[\'\"]");
    std::string content_copy=content;
   std:: smatch res;
    while(regex_search(content_copy,res,regu_pic)){
        foutpic<<"a picture:  "<<res[1].str()<<std::endl;
        content_copy=res.suffix();
    }
    foutpic.close();
}
void Htmlparser::getpara()
{
    //the previous version to find main point can only handle English website
    //for dont know how to match chinese using regex


    /*regex regu_p("<p[a-z0-9A-z\\s,.'’;&-:]*>[\n\r\t\f\v ]*([a-z0-9A-z\\s,.'’;&-:\"\n\r\t\f\v \\(\\)\\-]+)");
    while(regex_search(content_copy,res,regu_p)){
   foutpara<<"a para:  "<<res[1].str()<<endl;
    content_copy=res.suffix();
    }
    content_copy=content;
    */


   // so I gave up regex and try another vertion to find the main point
    std::fstream foutpara;
    foutpara.open("paragraph.txt",std::ios::app);
    std::string content_copy=content;
    std::string parabegin="<p";
    std::string paraend="</p>";
    while(content_copy.find(parabegin)!=std::string::npos)
    {
        std::string sentence=content_copy.substr(content_copy.find(parabegin),
        content_copy.find(paraend)-content_copy.find(parabegin));
        content_copy=content_copy.substr(content_copy.find(paraend)+1,
        content_copy.size()-content_copy.find(paraend)-1);
        if(sentence.find("href")!=std::string::npos)
            continue ;
        while(sentence.find("<")!=std::string::npos && sentence.find(">")!=std::string::npos)
        {   
            sentence=sentence.substr(sentence.find(">")+1,sentence.rfind("<")-1-sentence.find(">"));
        }
        foutpara<<sentence<<std::endl;
        
    }
    
}

