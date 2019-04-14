all : main.cpp initialize.o get.o HTMLparser.h
	g++ -o all main.cpp initialize.o get.o
initialize.o : initialize.cpp
	g++ -c initialize.cpp
get.o : get.cpp
	g++ -c get.cpp
clean :
	rm -rf *.o all