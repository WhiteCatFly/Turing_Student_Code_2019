prog: main.o bigint.o bigint.h
	g++ -std=c++17 -O2 -o prog main.o bigint.o
main.o: main.cpp bigint.h
	g++ -std=c++17 -O2 -c main.cpp
bigint.o: bigint.cpp bigint.h
	g++ -std=c++17 -O2 -c bigint.cpp

clean:
	rm main.o bigint.o prog