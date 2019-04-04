crawl : main.o crawl.h crawl.o
	g++ -o crawl main.o crawl.o
main.o : main.cpp
	g++ -c main.cpp
crawl.o : crawl.cpp
	g++ -c crawl.cpp
clean :
	rm main.o crawl.o crawl
