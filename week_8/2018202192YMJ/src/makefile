objects = main.o search_engine.o

prog: $(objects)
	g++ -std=c++11 -O2 -o prog $(objects)
main.o: main.cpp search_engine.h
	g++ -std=c++11 -O2 -c main.cpp
search_engine.o: search_engine.cpp search_engine.h
	g++ -std=c++11 -O2 -c search_engine.cpp