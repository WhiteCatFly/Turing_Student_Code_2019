###Homework2 
--
* 本次作业包含一个项目文件夹，用Makefile编译；

* 直接运行后会在当前目录下下载所有的网页信息；可以输入主函数参数来控制下载路径和爬取网页
  第一个参数是下载路径，默认是当前目录下，第二个参数是爬取的网页，默认是经济学院网页

* 其中用了一个 set 和一个 queue 来进行爬取，set中存放已经进入过 queue 的元素；
            
* 前面有一个数组表示黑名单，即不需要的一些内容；

* 最后是将相对地址添加为绝对地址以后再做其他操作。

* 运行make能生成一个文件web_crawl，执行后能够爬取7656个网页，耗时约53mins；

* （Update）使用类进行封装，其中只有Core为外部接口，直接爬取所有网页。