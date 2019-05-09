main: main.cpp bigint.o operator.o bigint.h
	g++ main.cpp bigint.o operator.o -o main 
bigint.o: bigint.cpp bigint.h
	g++ -c bigint.cpp -o bigint.o
operator.o: operator.cpp bigint.h
	g++ -c operator.cpp -o operator.o
clean:
	rm -f bigint.o operator.o
