main : main.o download.o htmlparser.o normalize.o
	g++ main.o download.o htmlparser.o normalize.o -o main
main.o : main.cpp htmlparser.h
	g++ -c main.cpp
download.o : download.cpp download.h
	g++ -c download.cpp
htmlparser.o : htmlparser.cpp download.h htmlparser.h normalize.h
	g++ -c htmlparser.cpp
normalize.o : normalize.cpp normalize.h
	g++ -c normalize.cpp
clean : 
	rm main main.o download.o htmlparser.o normalize.o