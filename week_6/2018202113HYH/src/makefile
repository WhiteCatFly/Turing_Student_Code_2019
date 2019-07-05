CC = g++

all : main.o crawler.o crawler.h parser.o parser.h
		$(CC) main.o crawler.o parser.o -o all
main.o : main.cpp crawler.h parser.h
		$(CC) -c main.cpp 
crawler.o : crawler.cpp crawler.h parser.h
		$(CC) -c crawler.cpp 
parser.o : parser.cpp parser.h
		$(CC) -c parser.cpp 
clean :
		rm -rf *.o
                  