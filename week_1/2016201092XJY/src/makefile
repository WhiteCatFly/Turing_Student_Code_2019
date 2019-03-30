edit: crawler.o HTMLFunc.o getContent.o
	g++ -std=c++11 crawler.cpp HTMLFunc.cpp getContent.cpp crawl.cpp -o edit

crawler.o: crawler.cpp HTMLFunc.h getContent.h
	g++ -std=c++11 -c crawler.cpp -o crawler.o

getContent.o: getContent.cpp getContent.h
	g++ -std=c++11 -c getContent.cpp -o getContent.o

HTMLFunc.o: HTMLFunc.cpp HTMLFunc.h
	g++ -std=c++11 -c HTMLFunc.cpp -o HTMLFunc.o

crawl.o: crawl.cpp crawl.h getContent.h HTMLFunc.o
	g++ -std=c++11 -c crawl.cpp -o crawl.o

clean:
	rm edit crawler.o getContent.o HTMLFunc.o crawl.o
