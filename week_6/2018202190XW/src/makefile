crawl : main.o Crawler.o Url.o TagNode.o Html.o StringModify.o
	g++ -std=c++17 -o crawl -O2 main.o Crawler.o Url.o TagNode.o Html.o StringModify.o
main.o : main.cpp Crawler.h Url.h TagNode.h Html.h
	g++ -std=c++17 -c -O2 main.cpp
Crawler.o : Crawler.cpp Crawler.h Url.h TagNode.h Html.h StringModify.h
	g++ -std=c++17 -c -O2 Crawler.cpp
Url.o : Url.cpp Url.h StringModify.h
	g++ -std=c++17 -c -O2 Url.cpp
TagNode.o : TagNode.cpp TagNode.h Html.h
	g++ -std=c++17 -c -O2 TagNode.cpp
Html.o : Html.cpp Html.h StringModify.h TagNode.h
	g++ -std=c++17 -c -O2 Html.cpp
StringModify.o : StringModify.cpp StringModify.h
	g++ -std=c++17 -c -O2 StringModify.cpp
clean :
	rm -r -f crawl main.o Crawler.o Url.o TagNode.o Html.o StringModify.o wget.log crawl.log page