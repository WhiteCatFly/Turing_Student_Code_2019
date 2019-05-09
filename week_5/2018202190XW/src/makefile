calc : main.o BigInt.o main.cpp BigInt.cpp BigInt.h
	g++ -o calc BigInt.o main.o
main.o : main.cpp BigInt.h
	g++ -c main.cpp
BigInt.o : BigInt.cpp BigInt.h
	g++ -c BigInt.cpp
clean :
	rm -r -f calc main.o BigInt.o