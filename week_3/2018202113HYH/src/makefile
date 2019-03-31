CC = g++

all : main.o class.o distinguish.o tools.h
	$(CC)  main.o class.o distinguish.o -o all
main.o : main.cpp tools.h
	$(CC) -c main.cpp 
class.o : class.cpp tools.h
	$(CC) -c class.cpp 
distinguish.o : distinguish.cpp tools.h
	$(CC) -c distinguish.cpp
clean :
	rm -rf *.o