## Description

A simple search engine with tf-idf ranking.

## Requirements

The corpus should be stored in "corpus.txt" in the same directory in a certain format.

Also, "thulac" and "models" should be in the same directory.

## Usage

```bash
$ make
$ ./prog
$ (after preprocessing, the program will prompt you to input words or phrases to search)
```

For the given word or phrase, the tf-idf value, the title, the url and the context, in which the word or pharase appears, of the relevant website will be shown in order. A maximum number of 10 websites can be shown.

## Examples

input a word or a phrase to search: 赵鑫 

34 pages found, top pages:

1 32.5652 赵鑫-师资科研-中国人民大学信息学院 info.ruc.edu.cn/academic_professor.php?teacher_id=55 赵鑫师资科研中国人民大学信息学院

2 28.0894 我院赵鑫老师在社交媒体数据挖掘方面取得系列成果-学院新闻-中国人民大学信息学院 info.ruc.edu.cn/news_convert_detail.php?id=1235 我院赵鑫老师在社交媒体数据挖掘方面取得系列成果学院新闻中国人民大学信息学院

...

input a word or a phrase to search: 赵鑫副教授

8 pages found, top pages:

1 11.2039 “明德图灵”项目团队赴香港交流访问-学院新闻-中国人民大学信息学院 info.ruc.edu.cn/news_detail.php?id=1541 明德图灵厚重人才成长支持计划一行共人赴香港进行交流访问。出访团队前往香港科技大学、香港中文大学两所知名高校进行学习参观，并与知名学者、人民大学杰出校友进行交流。本次出访由明德图灵项目导师赵鑫副教授、信息学院教务科娄蕙兰老师和孙大英老师带队。

2 11.2039 “明德图灵”项目团队赴香港交流访问-学院新闻-中国人民大学信息学院 info.ruc.edu.cn/news_convert_detail.php?id=1541 年月日至月日，明德图灵厚重人才成长支持计划一行共人赴香港进行交流访问。出访团队前往香港科技大学、香港中文大学两所知名高校进行学习参观，并与知名学者、人民大学杰出校友进行交流。本次出访由明德图灵项目导师赵鑫副教授、信息学院教务科娄蕙兰老师和孙大英老师带队。

...

## Efficiency

The preprocessing needs 5 seconds or so.

The query takes almost no time.