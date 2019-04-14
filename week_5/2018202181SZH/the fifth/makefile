all : main.cpp BigInteger.h BigIntegerFunction.o
	g++ -o all main.cpp BigInteger.h BigIntegerFunction.o
BigIntegerFunction.o : BigIntegerFunction.cpp
	g++ -c BigIntegerFunction.cpp
clean :
		rm *.o all
