adding : main.o BigInteger.o
	g++ main.o BigInteger.o -o adding
main.o : main.cpp BigInteger.h
	g++ -std=c++11 -c main.cpp -o main.o
BigInteger.o : BigInteger.cpp BigInteger.h
	g++ -std=c++11 -c BigInteger.cpp -o BigInteger.o
clean : 
	rm adding main.o BigInteger.o
