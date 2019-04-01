main: main.cpp crawler.o nor_url.o get_source.o 
	g++ main.cpp crawler.o get_source.o nor_url.o -o main 
crawler.o: crawler.cpp crawler.h
	g++ -c crawler.cpp -o crawler.o
nor_url.o: nor_url.cpp crawler.h
	g++ -c nor_url.cpp -o nor_url.o
get_source.o: get_source.cpp crawler.h
	g++ -c get_source.cpp -o get_source.o
clean:
	rm -f get_source.o nor_url.o crawler.o
