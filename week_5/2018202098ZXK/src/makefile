objects = main.o

prog: $(objects)
	g++ -std=c++17 -O2 -o prog $(objects)
main.o: main.cpp BigInt.h
	g++ -std=c++17 -O2 -c main.cpp BigInt.h

clean:
	rm $(objects)