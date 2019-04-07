main : main.o parser.o
	g++ -o main main.o tree.o
main.o : main.cpp
	g++ -c main.cpp
parser.o :
	g++ -c parser.cpp
clean :
	rm main main.o parser.o
run :
	./main http://info.ruc.edu.cn