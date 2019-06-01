pro : main.cpp parser.o crawler.o search.o
	g++ -std=c++11 -o pro main.cpp parser.o crawler.o search.o
parser.o : parser.cpp
	g++ -std=c++11 -c parser.cpp
crawler.o : crawler.cpp
	g++ -std=c++11 -c crawler.cpp
search.o : search.cpp
	g++ -std=c++11 -c search.cpp
clean :
	rm -rf crawler.o parser.o search.o pro
