# NaiveTextSearch

A very naive text search using tf-idf.

## Usage

namelist.data 保存了已经切词的文件的文件名  

```text
我院赵鑫老师在社交媒体数据挖掘方面取得系列成果 - 学院新闻 - 中国人民大学信息学院.txt
我院赵鑫老师在信息检索领域和数据挖掘方面取得系列成果 - 学院新闻 - 中国人民大学信息学院.txt
我院智慧养老研究所参与主办的第五届智慧养老与智慧医疗论坛顺利举行 - 学院新闻 - 中国人民大学信息学院.txt
我院智慧养老研究所成功承办养老信息化与标准化论坛 - 学院新闻 - 中国人民大学信息学院.txt
我院周春来博士的研究成果被国际人工智能顶级刊物Artificial Intelligence接收 - 学院新闻 - 中国人民大学信息学院.txt
我院组织开展2016年“我与社会主义核心价值观”主题班会活动 - 团学动态 - 中国人民大学信息学院.txt

```

```bash
$ make
0 ./prog namelist.data  
1 make clean
```

## Description

+ query内容取交集
+ load时间1-2s
+ query时间 1e-4~1e-3
