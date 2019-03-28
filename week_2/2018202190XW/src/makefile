crawl : main.o Crawler.o UrlParser.o StringModify.o
	g++ -std=c++17 -O2 -o crawl main.o Crawler.o UrlParser.o StringModify.o
main.o : main.cpp Crawler.h
	g++ -std=c++17 -O2 -c main.cpp
Crawler.o : Crawler.cpp Crawler.h UrlParser.h StringModify.h
	g++ -std=c++17 -O2 -c Crawler.cpp
UrlParser.o : UrlParser.cpp UrlParser.h StringModify.h
	g++ -std=c++17 -O2 -c UrlParser.cpp
StringModify.o : StringModify.cpp StringModify.h
	g++ -std=c++17 -O2 -c StringModify.cpp
clean :
	rm -r -f crawl main.o Crawler.o UrlParser.o StringModify.o wget.log page