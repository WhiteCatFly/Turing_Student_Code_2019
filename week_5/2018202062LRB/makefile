main : main.o BigInteger.o
	clang++ -o main main.o BigInteger.o
main.o : main.cpp BigInteger.h
	clang++ -c main.cpp
BigInteger.o : BigInteger.cpp BigInteger.h
	clang++ -c BigInteger.cpp
clean :
	rm main main.o BigInteger.o