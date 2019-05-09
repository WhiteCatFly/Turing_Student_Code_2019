#include <iostream>
#include "Spider.h"

int main(int argc, char const *argv[])
{
	
	Attribute arg = creatAttr(argc, argv);
	//采用了cookie 或者 header，使用SSpider版本， 否则采用Spider版本
	//采用reload就使用load加载已有数据，否则“从零开始”
	if(arg["cookie"].length() || arg["header"].length()){
		SSpider crawler(arg, arg["header"], arg["cookie"]);
		arg["reload"].length() ? crawler.load() : crawler.run();
	}
	else{
		Spider crawler(arg);
		arg["reload"].length() ? crawler.load() : crawler.run();
	}
	return 0;
}
