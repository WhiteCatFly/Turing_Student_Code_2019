main : test.o bignum.h bignum.o
	g++ -o test test.o bignum.o
test.o : test.cpp
	g++ -c test.cpp
bignum.o : bignum.cpp bignum.h
	g++ -c bignum.cpp
clean :
	rm test test.o bignum.o