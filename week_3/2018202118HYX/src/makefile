.PHONY:clean

main:parse_url.o main.cpp head.h
	g++ parse_url.o main.cpp -g -o main

parse_url.o:parse_url.cpp
	g++ -c parse_url.cpp

clean:
	-rm *.o main