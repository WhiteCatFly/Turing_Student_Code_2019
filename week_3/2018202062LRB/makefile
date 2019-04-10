main : main.o download.o find_append.o normalize.o
	clang++ main.o download.o find_append.o normalize.o -o main

main.o : main.cpp download.h find_append.h
	clang++ -c main.cpp
download.o : download.cpp download.h
	clang++ -c download.cpp
find_append.o : find_append.cpp find_append.h normalize.h
	clang++ -c find_append.cpp
normalize.o : normalize.cpp normalize.h
	clang++ -c normalize.cpp
clean : 
	rm main main.o download.o find_append.o normalize.o