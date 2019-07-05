prog : main.o TagNode.o HtmlParser.o PositionIndex.o Utility.o
	g++ -std=c++17 -O2 -o prog main.o TagNode.o HtmlParser.o PositionIndex.o Utility.o

main.o : PositionIndex.h Utility.h main.cpp
	g++ -std=c++17 -O2 -c main.cpp

Utility.o : Utility.h Utility.cpp
	g++ -std=c++17 -O2 -c Utility.cpp

PositionIndex.o : PositionIndex.h TagNode.h HtmlParser.h LAC.h PositionIndex.cpp
	g++ -std=c++17 -O2 -c PositionIndex.cpp

HtmlParser.o : TagNode.h HtmlParser.h HtmlParser.cpp
	g++ -std=c++17 -O2 -c HtmlParser.cpp

TagNode.o : TagNode.h TagNode.cpp
	g++ -std=c++17 -O2 -c TagNode.cpp

clean :
	rm -r -f prog main.o LAC.o HtmlParser.o TagNode.o Utility.o PositionIndex.o