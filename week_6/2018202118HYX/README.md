总共五个类
Get类专门用于获取url内容
Base类用于其他网站
Econ类专用于经济学院网站
Info类专用于信息学院网站
Parser类为HTMLparser

其中Econ和Info继承了Base类
Base、Econ、Info中BFS函数复合了Get类

wget中
加入日志记录 -a
断点重爬 -c

加入命令行参数

提供command函数，方便使用
