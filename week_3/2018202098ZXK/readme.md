# Spider of RUC
A navie spider that you can use your own config file.  
# Config
Your config file should be like the default one  
default.ini: #please ignore #  
Web_Base=http://econ.ruc.edu.cn/ #must has the ending char /  
Num_Thread=40 #number of threads  
Time_Sleep=300 #in microseconds  
Num_Tries=2 #try at most 2 times  
Time_Out=2 #in seconds  
Error_File=errfile.data #override the errfile if there exists one  
# Usage
If you don't provide the config file, use the default.ini automaticly.
```bash
$ make
0 ./prog [your config file]
```
# Output

Crawled webs will be saved in the current working directory.

# Description
Class Request:  
输入参数Url, 利用成员函数crawl下载, 通过getStatu查看是否成功下载, 若成功下载，可将下载的网页中的链接提取到Vector里面.  
Struct Config:  
用来保存设置的结构体,既保存Request需要的参数(like web_base)，也保存主程序需要的参数(like num_thread).  