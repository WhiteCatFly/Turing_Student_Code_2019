pro : main.cpp crawler.h parser.h crawler.o parser.o
	g++ -o pro main.cpp crawler.o
crawler.o : crawler.cpp
	g++ -c crawler.cpp
parser.o : parser.cpp
	g++ -c parser.cpp
clean :
	rm -rf crawler.o parser.o pro
