bighomework : main.o getcontent.o dfs.o main.c getcontent.c dfs.c
	g++ -o bighomework main.o getcontent.o dfs.o -std=c++11
main.o : main.c BigJob.h
	g++ -c main.c
dfs.o : dfs.c BigJob.h
	g++ -c dfs.c
getcontent.o : getcontent.c BigJob.h
	g++ -c getcontent.c


