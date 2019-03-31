# web_crawler

<br>

## Description 
Homework3 (2019.4.1)  
爬取某一网页下( 默认 http://econ.ruc.edu.cn )下的所有页面  
以url对应目录结构保存到本地指定目录( 默认download/ )下  


* main.cpp: 主程序，主体为bfs  
* my_config.cpp/.h: 参数配置
* my_fetcher.cpp/.h: 基于libcurl库的下载  
* my_crawler.cpp/.h: 对待爬取网页集合的维护及对url及网页内容的解析处理 
* my_res.h: 页面内容存储
* config.cfg: 配置文件

<br>

## Result
在较好网络环境下 6min 左右可爬取 7415 个页面  
( 含1个重定向 http://econ.ruc.edu.cn/en -> http://econ.ruc.edu.cn/en/ ) 

已排除以下格式文件下载 : 

.css,  .js,  .png,  .jpg,  .jpeg,  .ico,  .mp4,  .mp3,  .flv,
.xls,  .xlsx,  .doc,  .ppt,  .docx,  .pptx,  .rar,  .zip,  .7z,  .pdf,
mailto,  .JPG, javascript,  .bmp,  .gif

<br>

## Usage

本项目依赖于libcurl及libconfig  

```
$ make
$ ./run
```  
默认参数已在config.cfg中，其中各参数含义及默认值如下：
* root_url :  根目录，默认值为 "http://econ.ruc.edu.cn/"
* MAX_FAIL_TIME :  单个url失败重连最大次数，默认值为 10
* MAX_EASY_TIME :  单个easy_handle最长时限(ms)，默认值为 3000
* MAX_EASY_NUM :  单次最大下载页面数，默认值为 64
* FOUT_FILENAME :  正常下载记录文件，默认值为 "visit.log"
* FERR_FILENAME :  异常下载记录文件，默认值为 "error.log"
* SAVE_PATH :  页面下载路径，默认值为 "download/"

<br>

## Known Issues 
非常不建议在RUC网络下运行，会蓝屏( 我也不知道为什么
