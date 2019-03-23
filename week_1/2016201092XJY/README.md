
爬取页面：  6155个       用时：  1463s

getContent.cpp:  用于获取页面内容，内有2个函数 
    inline void downloadURL(const string & url,const string & dirname);//下载页面内容并保存至本地
    string getContent(const string & url,const string & dirname);//以字符串形式返回页面内容

HTMLFunc.cpp:    用于处理HTML内容，内有1个函数
    void parseURLs(const string & page_content, const string & current_url, set <string> &urls_current_page); 
    //分析当前URL的页面内容，将其中所有URL链接放到集合里

crawl.cpp:       爬虫核心，内有1个函数
    void crawl(const string & root)   //从根URL开始爬取整个网站的内容,默认从信院首页开始

edit: 	         最后生成的可执行文件

