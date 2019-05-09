# WebCrawler

## Description 
Homework6 / Midterm (2019.5.9)  

爬取某一网页下( 默认 http://econ.ruc.edu.cn )下的所有页面  
以url对应目录结构保存到本地指定目录( 默认download/ )下  
支持断点重爬

## Usage

本项目依赖于libcurl及libconfig  

重新爬取
```
$ make
$ ./run
```  

继续上一次爬取
```
$ make
$ ./run -c
```

默认参数已在config.cfg中，其中各参数含义及默认值如下：
* root_url :  根目录，默认值为 "http://econ.ruc.edu.cn/"
* MAX_FAIL_TIME :  单个url失败重连最大次数，默认值为 10
* MAX_EASY_TIME :  单个easy_handle最长时限(ms)，默认值为 3000
* MAX_EASY_NUM :  单次最大下载页面数，默认值为 64
* FOUT_FILENAME :  正常下载日志文件，默认值为 "visit.log"
* FERR_FILENAME :  异常下载日志文件，默认值为 "error.log"
* FLOG_FILENAME :  缓存日志文件，默认值为 ".log"
* SAVE_PATH :  页面下载路径，默认值为 "download/"

## Known Issues 
非常不建议在RUC网络下运行，会蓝屏( 我也不知道为什么
