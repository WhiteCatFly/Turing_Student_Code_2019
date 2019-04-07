# HTMLParser
## intro

A very naive HTMLParser  
author: ZXK

Feature
+  class Tag and class HTMLParser
+  use REGEX
+  use DOM tree

## Usage
```
make
./htmlParser
```
Then follow the instruction
##OUTPUT
Links.txt in current working directory
Texts.txt in current working directory


### HtmlParser Interface
+  HTMLParser(const &string)
+  HTMLParser(ifstream& in): two constructor
+  string getTitle() : return title
+  int getTexts(string& filename): return the num of texts and store it in file
+  int getLinks(string& filename): return the num of links and store it in file
+  Tag* find(string& tag_name): find the first tag whose name is the "tag_name"
+  int find_all(string& tag_name, std::vector<Tag*> &v):find all the tags and put them in the vector, return num

### Tag Interface
+ Tag* prev()
+ Tag* next()
+ Tag* parent()
+ Tag* son() //if not exists, return nullptr.
+ string operator[](string& key):like tagA["href"]
+ Tag* find(string& tag_name)
+ int find_all(string& tag_name, std::vector<Tag*> &v):The same as above

### To Do 
+  处理网页注释（在本程序中，所有的注释被暴力的忽略了……
+  提高鲁棒性（本程序对不"规范”的网页容错性一般……

###设计思路
参考了[W3C Dom](https://www.w3.org/DOM/)
