CC = g++

all : main.o textquery.o textquery.h queryresult.o queryresult.h
		$(CC) main.o textquery.o queryresult.o -o all
main.o : main.cpp textquery.h queryresult.h
		$(CC) -c main.cpp 
textquery.o : textquery.cpp textquery.h
		$(CC) -c textquery.cpp 
queryresult.o : queryresult.cpp queryresult.h textquery.h
		$(CC) -c queryresult.cpp 
clean :
		rm -rf *.o
                  