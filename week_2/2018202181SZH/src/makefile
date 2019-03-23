CC = g++

all : main.cpp getcontent.h parse.h getcontent.o parse.o
	$(CC) -o all main.cpp getcontent.o parse.o
parse.o : parse.cpp
	$(CC) -c parse.cpp
getcontent.o : getcontent.cpp
	$(CC) -c getcontent.cpp
clean :
	rm -rf getcontent.o parse.o all
