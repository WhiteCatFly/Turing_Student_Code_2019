bigint : main.o operatoradd.o operator_iostream.o Biginteger.o main.cpp operatoradd.cpp operator_iostream.cpp Biginteger.cpp 
	g++ -o bigint main.o operatoradd.o operator_iostream.o Biginteger.o 
main.o : main.cpp Biginteger.h
	g++ -c main.cpp
operatoradd.o : operatoradd.cpp Biginteger.h
	g++ -c operatoradd.cpp
operator_iostream.o : operator_iostream.cpp Biginteger.h
	g++ -c operator_iostream.cpp
Biginteger.o :  Biginteger.cpp Biginteger.h
	g++ -c Biginteger.cpp

