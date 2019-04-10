crawl : main.o Crawler.o Url.o StringModify.o
	g++ -std=c++17 -O2 -o crawl main.o Crawler.o Url.o StringModify.o
main.o : main.cpp Crawler.h Url.h
	g++ -std=c++17 -O2 -c main.cpp
Crawler.o : Crawler.cpp Crawler.h Url.h StringModify.h
	g++ -std=c++17 -O2 -c Crawler.cpp
Url.o : Url.cpp Url.h StringModify.h
	g++ -std=c++17 -O2 -c Url.cpp
StringModify.o : StringModify.cpp StringModify.h
	g++ -std=c++17 -O2 -c StringModify.cpp
clean :
	rm -r -f crawl main.o Crawler.o Url.o StringModify.o wget.log page