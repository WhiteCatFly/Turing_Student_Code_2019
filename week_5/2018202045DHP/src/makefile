main : main.cpp bigint.h bigint_support.o bigint_IO.o
	g++ main.cpp bigint_support.o bigint_IO.o -o main
main_ : main_.cpp bigint.h bigint_support.o bigint_IO.o
	g++ main_.cpp bigint_support.o bigint_IO.o -o main_
bigint_support.o : bigint.h bigint_support.cpp
	g++ -c bigint_support.cpp
bigint_IO.o : bigint.h bigint_IO.cpp
	g++ -c bigint_IO.cpp
clear:
	rm -rf main main_ bigint_support.o bigint_IO.o