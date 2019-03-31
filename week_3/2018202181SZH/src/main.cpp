#include"unit.h"
using namespace std;
string sensitive_words[100]={
    ".com",".org",".ru",
    "comsenz","discuz","bbs","rdjjlt",".css",".doc",".docx",".xls",".xlsx",".txt",".jpg",".png","bmp",
    ".jpeg",".flv",".mp4",".avi","@ruc.edu.cn",".pdf","#",".zip",".ppt","javascript",
    ".7z",".rar",".CSS",".DOC",".DOCX","mailto",".XLS",".XLSX",".TXT",".JPG",".PNG","BMP","rar","@163",
    ".JPEG","file://",".FLV",".MP4",".AVI","@RUC.EUD.CN",".PDF",".ZIP",".7Z",".RAR","words_end"
};
string root_url ;

int main(){
    
    input_first_url(root_url);//读入根目录
    website run;
    run.Bfs();
    return 0;
}

