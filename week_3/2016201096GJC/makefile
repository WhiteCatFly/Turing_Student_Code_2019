crawler : main.o CmdOrder.o html.o
	g++ main.o CmdOrder.o html.o -o crawler
main.o : main.cpp html.h CmdOrder.h
	g++ -std=c++11 -c main.cpp -o main.o
html.o : html.cpp html.h
	g++ -std=c++11 -c html.cpp -o html.o
CmdOrder.o : CmdOrder.cpp CmdOrder.h
	g++ -std=c++11 -c CmdOrder.cpp -o CmdOrder.o
clean : 
	rm crawler main.o CmdOrder.o html.o
