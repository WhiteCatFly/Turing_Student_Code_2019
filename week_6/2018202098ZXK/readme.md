
# WebSpider

A navie spider.  

## Usage

If you don't provide these arguments , use default.

```bash
$ make
  ./crawler url [-timeout ..]  [-sleep ..] [-thread ..] [-reload ..] [-error ..] [-runlog ..] [-header ..] [-cookie ..]  
  make clean
```

## Output

Crawled webs will be saved in the **current working directory.**

## Argument

Your arguments **should** follow these rules

+ 命令的格式必须是 ./crawler url -命令1 参数 -命令2 参数 .. 

+ 命令的顺序并不重要

+ -timeout 设置超时的时间 单位秒

+ -sleep 设置休眠时间 单位毫米

+ -thread 设置线程数目

+ -reload 设置从断点重爬的数据来源，默认RUN.log

+ -error 设置错误信息的输出文件

+ -runlog 设置队列出入信息的记载源，用于支持reload

+ -header 设置请求头,用于~~欺骗~~服务器

+ -cookie 设置cookie,用于~~欺骗~~服务器

> header文件样例,可以通过浏览器调试工具直接复制

```text
Host: info.ruc.edu.cn
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:63.0) Gecko/20100101 Firefox/63.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: keep-alive
```

特别注意：一旦Header中出现**Accept-Encoding: gzip, deflate**,本程序会接收gzip格式的返回文件，节省流量，但是可能由于传递过程中“丢包”等，造成解压缩失败，损失部分信息！

> cookie文件样例,建议使用浏览器拓展Exports cookies生成

```text
# Netscape HTTP Cookie File

forum.ubuntu.org.cn	FALSE	/	FALSE	1588603957	ubuntuforum_u	1
forum.ubuntu.org.cn	FALSE	/	FALSE	1588603957	ubuntuforum_k	
forum.ubuntu.org.cn	FALSE	/	FALSE	1588603957	ubuntuforum_sid	0ac294190e3fce9624f2fc92386cb80f

```

## Description
主要组件有五个.

+ Attribute用来保存配置

+ HTMLParser用来解析网页

+ Request用来执行爬取请求,输入url后可以下载该网页，并且可以通过复合的HTMLParser提取连接

+ Spider是封装过后的爬虫，可以run, reload.

+ SSpider在继承Spider的基础上添加了Header,cookie用来~~欺骗~~服务器，同时可以采用gzip格式传输数据省流，加速。

