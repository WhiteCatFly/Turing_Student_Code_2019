edit : main.o cmdOrder.o getCmdResult.o htmlParse.o
	g++ main.o cmdOrder.o getCmdResult.o htmlParse.o -o edit
main.o : main.cpp getCmdResult.h htmlParse.h cmdOrder.h
	g++ -std=c++11 -c main.cpp -o main.o
getCmdResult.o : getCmdResult.cpp getCmdResult.h
	g++ -std=c++11 -c getCmdResult.cpp -o getCmdResult.o
htmlParse.o : htmlParse.cpp htmlParse.h
	g++ -std=c++11 -c htmlParse.cpp -o htmlParse.o
cmdOrder.o : cmdOrder.cpp cmdOrder.h
	g++ -std=c++11 -c cmdOrder.cpp -o cmdOrder.o
clean : 
	rm edit main.o getCmdResult.o htmlParse.o cmdOrder.o
