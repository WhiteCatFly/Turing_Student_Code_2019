爬虫结果:共177层7070个网页,耗时65min
Html类私有成员:
    _road:html文件的存储文件夹编号
    _i:html文件在文件夹中的编号
	_htmlname:html文件的完整路径
	_starturl:初始url,也是每个html对应url的前半部分
Html类公有成员:
    Html():默认构造函数
	Html(int i, int road, string starturl):自定义的构造函数
	_single_url_set:静态成员变量,记录这一级将要下载的htmlname
	_history_url_set:静态成员变量,记录下载过的所有htmlname
	HtmlName():生成_htmlname
	GenerateVector(string strurl):把正则表达式匹配到的url做初步筛选和标准化
	HtmlParse(string RegularExperssion):传入正则表达式匹配url并去重
	ShowCount():const函数,爬虫结束后输出_history_url_set的大小
CmdOrder.h/cpp文件包含六个函数:
	DownloadStartHtml(string starturl):下载初始url
	DownloadUrlLink(string url):生成下载url所需要的终端命令前半部分
	DownloadHtml(string strroadadd, int j, string url):生成完整终端命令
	GetCmdResult(const string& strCmd):获取终端命令的运行结果
	CountFiles(int road):计算指定编号文件夹下的文件总数
	
	
