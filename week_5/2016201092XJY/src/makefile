edit: main.o BigInteger.o
	g++ -std=c++11 main.cpp BigInteger.cpp -o edit

main.o: main.cpp BigInteger.h
	g++ -std=c++11 -c main.cpp -o main.o

BigInteger.o: BigInteger.cpp BigInteger.h
	g++ -std=c++11 -c BigInteger.cpp -o BigInteger.o

clean:
	rm edit main.o BigInteger.o
