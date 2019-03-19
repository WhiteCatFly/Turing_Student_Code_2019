crawl : Crawl.o UrlParser.o StringModify.o
	g++ -std=c++17 -O2 -o crawl Crawl.o UrlParser.o StringModify.o
Crawl.o : Crawl.cpp Crawl.h UrlParser.h StringModify.h
	g++ -std=c++17 -O2 -c Crawl.cpp
UrlParser.o : UrlParser.cpp UrlParser.h StringModify.h
	g++ -std=c++17 -O2 -c UrlParser.cpp
StringModify.o : StringModify.cpp StringModify.h
	g++ -std=c++17 -O2 -c StringModify.cpp
clean :
	rm -r -f crawl Crawl.o UrlParser.o StringModify.o wget.log page