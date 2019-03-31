本文档用于解释代码思路与运行思路，以及运行结果。

使用代码的方式：
make
./all   
输入想要爬取网站的根目录，如：econ.ruc.edu.cn

代码思路：
1.getcontent.cpp  获得当前url的源码并且把它存在一个string中
2.parse.cpp  来取得当前的url下面的所有源代码
3.init.cpp是class的初始化
4.bfs.cpp为class里的公共接口

总计：爬取网页7270  用时32'26'' 

  