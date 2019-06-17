# Search Engine

## Description 
Homework9 on 2019.5.23  
一个简单的基于 TF-IDF 排序的搜索引擎（C++版） 

## Requirement
* THULAC  

## Usage
请将所需检索页面放在`./download/`目录下  
请将THULAC所需分词模型置于`./models/`目录下  

```
$ make
$ ./run
```  

在`>>>`提示符后输入想要查询的内容  
输入`q`以退出程序

## Result
加载时间约为`45s`

当输入查询关键词后，每个页面按照以下结构返回查询结果:

* 编号（Result #）
* 相关度（Relevance）
* 页面地址（Url）
* 关键词（Keywords）
* 页面前100字内容（View）  

例如，查询关键字`赵鑫`得到前两个结果如下：

```  
Result #1
[ Relevance ] 0.0380132
[ Url ] download/news_convert_detail.php?id=1235
[ Keywords ] 社交 论文 赵鑫 Wayne 篇 媒体 appear To Xin IJCAI
[ View ]
联系我们|院长信箱|English|教师入口首&nbsp&nbsp&nbsp&nbsp&nbsp页学院概况新闻公告人才培养师资科研学生发展对外交流院友之家学院简介院长寄语现任领导机构设置联系我们学院新闻学院公告信息相册新闻人物信息影像本科生学术型硕士工程硕士博士生在职工程硕士同等学力教育公告学生党建团学风采就业实习学生事务奖励资助师资队伍学术科研外事新闻交流信息合作项目办事指

Result #2
[ Relevance ] 0.032634
[ Url ] download/news_convert_detail.php?id=1087
[ Keywords ] Xin Zhao 论文 2014. 赵鑫 篇 Hongfei Yuexin Yulan In
[ View ]
联系我们|院长信箱|English|教师入口首&nbsp&nbsp&nbsp&nbsp&nbsp页学院概况新闻公告人才培养师资科研学生发展对外交流院友之家学院简介院长寄语现任领导机构设置联系我们学院新闻学院公告信息相册新闻人物信息影像本科生学术型硕士工程硕士博士生在职工程硕士同等学力教育公告学生党建团学风采就业实习学生事务奖励资助师资队伍学术科研外事新闻交流信息合作项目办事指
```

## Illustration
本次作业大概是把上次的python版改写成C++版  
使用了之前 HTMLParser 作业中的 `DOM``Lexer`类、`tagString``Token`部分 进行正文提取  
新增：  
`Document`类管理单个页面  
`Library`类管理页面索引  
`search`部分封装THULAC  