.PHNOY:clean

main:main.cpp head.h BigInteger.o add&sub.o mult.o div&remain.o
	g++ -o main main.cpp BigInteger.o add&sub.o mult.o div&remain.o

BigInteger.o: BigInteger.cpp
	g++ -c BigInteger.cpp

add&sub.o: add&sub.cpp
	g++ -c add&sub.cpp

mult.o:mult.cpp
	g++ -c mult.cpp

div&remain.o:div&remain.cpp
	g++ -c div&remain.cpp

clean:
	-rm *.o main