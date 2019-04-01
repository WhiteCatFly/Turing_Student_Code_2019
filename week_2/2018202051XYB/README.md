# web_crawler

Homework2 (2019.3.24)  
爬取 http://info.ruc.edu.cn 下的所有页面  
以url对应目录结构保存到本地 download/ 下  

main.cpp: 主程序  
bfs.cpp: bfs 部分 及 文件保存  
my_curl.cpp: 基于 multi_handle 的页面下载   
my_string.cpp: 对url的处理 及 对网页内容的解析处理  


## Result
在正常网络环境下 4min 左右可爬取 6300+ 个页面  
已排除文件下载  

## Usage
```
$ make
$ ./run [error_filename] [success_filename]
```
链接失败信息存入 error_filename ， 默认为 error.txt  
下载成功信息存入 success_filename ， 默认为 success.txt

## Known Issues 
非常不建议在RUC网络下运行，会蓝屏（我也不知道为什么
