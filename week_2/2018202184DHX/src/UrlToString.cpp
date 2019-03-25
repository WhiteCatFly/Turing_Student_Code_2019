#include"UrlToString.h"
#include"bfs.h"
void FileToString(int count)                                    //store the content in url
{
    page_content.clear();
    char temp[1000];
    sprintf(temp,"%d.html",count);
    FILE *fp = fopen(temp,"r");
    if(fp == NULL)
    {
        std::cout << temp << " File Open Error!" << std::endl;
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
    return ;
};
