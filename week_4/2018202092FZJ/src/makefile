parser: parser.o main.o extract.o
	g++ -o parser parser.o main.o extract.o
	rm -f *.o
parser.o: parser.h parser.cpp
	g++ -c parser.cpp -std=c++11
main.o: parser.h main.cpp
	g++ -c main.cpp -std=c++11
extract.o: parser.h extract.cpp
	g++ -c extract.cpp -std=c++11
