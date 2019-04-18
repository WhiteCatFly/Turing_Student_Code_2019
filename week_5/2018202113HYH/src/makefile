CC = g++

all : main.o BigInteger.o BigInteger.h
	$(CC) main.o BigInteger.o -o all
main.o : main.cpp BigInteger.h
	$(CC) -c main.cpp 
BigInteger.o : BigInteger.cpp BigInteger.h
	$(CC) -c BigInteger.cpp 
clean :
	rm -rf *.o

