parser : main.o HTMLParser.o CmdOrder.o
	g++ main.o HTMLParser.o CmdOrder.o -o parser
main.o : main.cpp HTMLParser.h
	g++ -std=c++11 -c main.cpp -o main.o
HTMLParser.o : HTMLParser.cpp HTMLParser.h
	g++ -std=c++11 -c HTMLParser.cpp -o HTMLParser.o
CmdOrder.o : CmdOrder.cpp CmdOrder.h
	g++ -std=c++11 -c CmdOrder.cpp -o CmdOrder.o
clean : 
	rm parser main.o HTMLParser.o CmdOrder.o
