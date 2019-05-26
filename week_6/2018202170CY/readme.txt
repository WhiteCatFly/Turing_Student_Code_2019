编译方法：
    make
运行方法：
    ./main + 爬取的根目录 + 存储爬取结果的文件夹路径 + wget的命令及参数 + "continue"(继续爬取)/"restart"(重新爬取) (参见makefile里的示例)
运行结果：
    爬取信息学院官网结果:
        共6390个网页
        时间20min左右
功能：
    可爬取指定的网页
    支持断点重爬，日志记录
内容：
    有三个类BaseCrawler, AdvancedCrawler, Parser
    使用了继承与复合
