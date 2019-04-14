BigInteger : main.o BigInteger.o
	g++ -o BigInteger main.o BigInteger.o

main.o : main.cpp BigInteger.cpp BigInteger.h
	g++ main.cpp -c -Wall

BigInteger.o : BigInteger.cpp BigInteger.h
	g++ BigInteger.cpp -c -Wall

clean :
	rm *.o
