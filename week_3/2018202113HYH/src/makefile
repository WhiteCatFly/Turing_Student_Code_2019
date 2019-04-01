CC = g++

all : main.o get.o search.o work.o get.h search.h work.h
	$(CC)  main.o work.o get.o search.o -o all
main.o : main.cpp search.h get.h work.h
	$(CC) -c main.cpp 
get.o : get.cpp get.h
	$(CC) -c get.cpp 
work.o : work.cpp work.h
	$(CC) -c work.cpp
search.o : search.cpp search.h get.h work.h
	$(CC) -c search.cpp	
clean :
	rm -rf *.o