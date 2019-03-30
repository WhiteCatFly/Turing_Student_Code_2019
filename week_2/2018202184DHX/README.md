###Homework2 
--
* 本次作业包含一个项目文件夹，用Makefile编译；

* 运行后会在当前目录下下载所有的网页信息；

* 其中用了一个 set 和一个 queue 来进行爬取，set中存放已经进入过 queue 的元素；
            
* 前面有一个数组表示黑名单，即不需要的一些内容；

* 最后是将相对地址添加为绝对地址以后再做其他操作。

* （update）运行make能生成一个文件web_crawl，执行后能够爬取6350个网页；

* （update）分为了bfs核心算法， StringOperate处理string，和UrlToString下载三个部分。
