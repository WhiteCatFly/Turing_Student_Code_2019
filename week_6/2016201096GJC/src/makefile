crawler: main.o CmdOrder.o html.o HTMLParser.o HTMLParserBase.o easylogging++.o
	g++ main.o CmdOrder.o html.o HTMLParser.o HTMLParserBase.o easylogging++.o -o crawler
main.o: main.cpp html.h CmdOrder.h HTMLParser.h HTMLParserBase.h easylogging++.h
	g++ -std=c++11 -c main.cpp -o main.o
html.o: html.cpp html.h
	g++ -std=c++11 -c html.cpp -o html.o
CmdOrder.o: CmdOrder.cpp CmdOrder.h
	g++ -std=c++11 -c CmdOrder.cpp -o CmdOrder.o
HTMLParser.o: HTMLParser.cpp HTMLParser.h
	g++ -std=c++11 -c HTMLParser.cpp -o HTMLParser.o
HTMLParserBase.o: HTMLParserBase.cpp HTMLParserBase.h
	g++ -std=c++11 -c HTMLParserBase.cpp -o HTMLParserBase.o
easylogging++.o: easylogging++.cc easylogging++.h
	g++ -std=c++11 -c easylogging++.cc -o easylogging++.o
clean : 
	rm crawler main.o CmdOrder.o html.o HTMLParser.o HTMLParserBase.o easylogging++.o
