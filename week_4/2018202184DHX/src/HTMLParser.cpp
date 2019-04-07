#include "HTMLParser.h"

/*Parser::Parser(std::stringstream stream,std::string website_)
{
    page_content.clear();
    website = website_;
    if(website.find("http:\/\/",0) != website.npos)          
    {
        website.erase(website.begin(), website.begin() + sizeof("http:\/\/"));
    };
    prefixion = website.substr(0,website.find_first_of('/'));
    stream >> page_content;
    SetUrl();
};*/

Parser::Parser(const char *filename,std::string website_)
{
    FILE *fp = fopen(filename,"r");
    page_content.clear();
    website = website_;
    if(website.find("http:\/\/",0) != website.npos)          
    {
        website.erase(website.begin(), website.begin() + sizeof("http:\/\/"));
    };
    if(website.find_first_of('/') != website.npos)
    prefixion = website.substr(0,website.find_first_of('/'));
    if(fp == NULL)
    {
        std::cout << filename << " File Open Error!" << std::endl;
    }
    else
    {
        char c = fgetc(fp);
        while(c != EOF){
            page_content.push_back(c);
            c = fgetc(fp);
        }
    }
    fclose(fp);
    SetUrl();
};

void Parser::Title()
{
    int pos_begin;
    int pos_end;
    std::string title;
    if(page_content.find("<title>",0) != page_content.npos)
    {
        pos_begin = page_content.find("<title>",0) + sizeof("<title>");
        pos_end = page_content.find("</title>",0);
        title = page_content.substr(pos_begin,pos_end - pos_begin);
        std::cout << title << std::endl;
    }
    else
    {
        std::cout << "there is no title" <<std::endl;
    }
};
void Parser::Body()
{
    int pos_begin;
    int pos_end;
    std::string body;
    if(page_content.find("<body>",0) != page_content.npos)
    {
        pos_begin = page_content.find("<body>",0) + sizeof("<body>");
        pos_end = page_content.find("</body>",0);
        body = page_content.substr(pos_begin,pos_end - pos_begin);
        std::cout << body << std::endl;
    }
    else
    {
        std::cout << "there is no body" <<std::endl;
    }  
};
void Parser::Url()
{
    std::set<std::string>::iterator it;
    for(it = url_already_saved.begin();it != url_already_saved.end();it++)
    {
        std::cout << *it << std::endl;
    }
};
void Parser::SetUrl()
{
    const std::regex regex ("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    std::smatch res;
    while(regex_search(page_content,res,regex))
    {
        std::string url = res[2].str();
        if(BlackListCheck(url))
        {
            if(JudgeReOrAb(url))
            {
                AbsoluteSite(url);
            }
            else
            {
                RelativeSite(url);
            }
        }
        page_content = res.suffix();
    }
};
bool Parser::BlackListCheck(std::string url)
{
    for(int i = 0 ; i < sizeof(BlackList) / MAX ; i++)
    {
        if(url.find(BlackList[i],0) != url.npos)
        {
            return false;
        }
    }
    return true;
};

bool Parser::JudgeReOrAb(std::string url)
{
    if(url.find("http:\/\/",0) != url.npos)
    return true;
    else
    {
        return false;
    }
};

void Parser::RelativeSite(std::string url)
{
    std::string tempo;
    tempo.clear();
    if(url.find(".php",0) != url.npos)
    {
        if(*url.begin() == '/')    
        {
            tempo = prefixion + url;
        }
        else
        {
            tempo = prefixion + '/' + url;
        }
    url_already_saved.insert(tempo);
    }
    else if(url.find(".html",0) != url.npos)
    {
        if(*url.begin() == '/')    
        {
            tempo = prefixion + url;
        }
        else
        {
            tempo = prefixion + '/' + url;
        }
    url_already_saved.insert(tempo);
    }
    else if(url.find('.',0) == url.npos)
    {
        if(*url.begin() == '/')    
        {
            tempo = prefixion + url;
        }
        else
        {
            tempo = prefixion + '/' + url;
        }
    url_already_saved.insert(tempo);
    }
    return;
};

void Parser::AbsoluteSite(std::string url)
{
    if(url.find("http:\/\/",0) != url.npos)          
    {
        url.erase(url.begin() ,url.begin() + 7);
        if(url.find(prefixion,0) != url.npos)
        {
            url_already_saved.insert(url);
        }
    }
    return;
};

Parser::~Parser()
{};