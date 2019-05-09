main : main.o BigInteger.o BigInteger.h 
	@g++ -o run main.o BigInteger.o 
main.o : main.cpp BigInteger.h 
	@g++ -c main.cpp
BigInteger.o : BigInteger.cpp BigInteger.h
	@g++ -c BigInteger.cpp
clean :
	@rm -rf *.o

check : checker.cpp BigInteger.o BigInteger.h
	@g++ -o checker checker.cpp BigInteger.o 
	@./checker