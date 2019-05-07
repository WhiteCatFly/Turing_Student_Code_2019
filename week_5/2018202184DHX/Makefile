.PHONY : clean

main : main.o BigInteger.o BigInteger.h
	@g++ -o BigInteger main.o BigInteger.o
main.o : main.cpp BigInteger.h 
	@g++ -c main.cpp
BigInteger.o : BigInteger.cpp BigInteger.h 
	@g++ -c BigInteger.cpp
clean :
	@rm -f *.o BigInteger print.out