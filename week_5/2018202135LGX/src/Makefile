aBigInteger:main.o BigInteger.o
	g++ main.o BigInteger.o -o aBigInteger
main.o:main.cpp BigInteger.h
	g++ -c main.cpp -o main.o
BigInteger.o:BigInteger.cpp BigInteger.h
	g++ -c BigInteger.cpp -o BigInteger.o
clean:
	rm -rf *.o aBigInteger
