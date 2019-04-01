CC = g++

all : main.cpp unit.h getcontent.o parse.o Bfs.o init.o
	$(CC) -o all main.cpp getcontent.o parse.o Bfs.o init.o
parse.o : parse.cpp
	$(CC) -c parse.cpp
getcontent.o : getcontent.cpp
	$(CC) -c getcontent.cpp
Bfs.o : Bfs.cpp
	$(CC) -c Bfs.cpp
init.o : init.cpp
	$(CC) -c init.cpp
clean :
	rm -rf  parse.o getcontent.o Bfs.o init.o all
