bighomework : main.o BigJob.o main.c BigJob.c
	g++ -o bighomework main.o BigJob.o -std=c++11
main.o : main.c BigJob.h
	g++ -c main.c
BigJob.o : BigJob.c BigJob.h
	g++ -c BigJob.c

