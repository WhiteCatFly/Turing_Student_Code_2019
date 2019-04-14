CC = g++

all : main.o parser.o parser.h
	$(CC) main.o parser.o -o all
main.o : main.cpp parser.h
	$(CC) -c main.cpp 
parser.o : parser.cpp parser.h
	$(CC) -c parser.cpp 
clean :
	rm -rf *.o