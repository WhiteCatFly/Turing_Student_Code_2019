.PHONY: clean

main: main.cpp something.o something.h
	g++ main.cpp something.o -o main

something.o:something.cpp
	g++ -c something.cpp

clean:
	-rm *.o main