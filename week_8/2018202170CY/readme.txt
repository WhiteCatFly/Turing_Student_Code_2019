编译命令：make
运行命令：make run
命令行参数说明：
	./main root directory wget_method crawler_method
	root表示爬取的根
	directory表示爬取结果存储路径
	wget_method表示wget的命令
	crawler_method："restart"表示重新爬取，"continue"表示从断点处重新爬取
运行时在"please putin a string"出现后输入查询的字符串即可
运行时需要在当前目录下存在before_seperation和after_seperation两个文件夹
thulac和分词需要的models未上传
