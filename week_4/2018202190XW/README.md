# Homework 4
HTMLpaser
build a tree structure for the html content
construct by the url or the path of the local file


## Usage
```
make
./paser -h
-f <file_name>
-u <url> <save_file_folder>
```

##For Example

1.html is like this
```html
<head>
	<title>中国人民大学信息学院</title>
</head>
<body>
	<div>
		<a href="http://www.kkeevviinnn.com">qwq</a>
	</div>
	<!--Comment-->
</body>
```
```
./paser -f 1.html
```
output is like
```
Text  ﻿
TagNode(head)
	TagNode(title)
		Text  中国人民大学信息学院
TagNode(body)
	TagNode(div)
		TagNode(a)
		 [Attribute] href = http://www.kkeevviinnn.com
			Text  qwq
	Comment  <!--Comment-->
```
and then you would be asked
```
what do you want to do next?
1.parse title 2.parse text 3.parse href 4.print 5.exit
```
try each
```
what do you want to do next?
1.parse title 2.parse text 3.parse href 4.print 5.exit
1
中国人民大学信息学院
what do you want to do next?
1.parse title 2.parse text 3.parse href 4.print 5.exit
2

中国人民大学信息学院
qwq
what do you want to do next?
1.parse title 2.parse text 3.parse href 4.print 5.exit
3
http://www.kkeevviinnn.com
what do you want to do next?
1.parse title 2.parse text 3.parse href 4.print 5.exit
5
```
