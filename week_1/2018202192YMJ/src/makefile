objects = main.o extract_href.o\
		  normalizer.o crawl.o bfs.o

prog : $(objects)
	g++ -std=c++17 -O2 -o prog $(objects)
main.o : main.cpp
	g++ -std=c++17 -O2 -c main.cpp
extract_href.o : extract_href.cpp
	g++ -std=c++17 -O2 -c extract_href.cpp
normalizer.o : normalizer.cpp
	g++ -std=c++17 -O2 -c normalizer.cpp
crawl.o : crawl.cpp
	g++ -std=c++17 -O2 -c crawl.cpp
bfs.o : bfs.cpp
	g++ -std=c++17 -O2 -c bfs.cpp

clean :
	rm $(objects) wget-log
