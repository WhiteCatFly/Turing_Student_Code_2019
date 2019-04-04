.PHONY:clean

main : main.cpp head.h getcontent.o parse.o BFS.o
	g++ -o main main.cpp getcontent.o parse.o BFS.o
parse.o : parse.cpp
	g++ -c parse.cpp
getcontent.o : getcontent.cpp
	g++ -c getcontent.cpp
BFS.o : BFS.cpp
	g++ -c BFS.cpp
clean :
	-rm  *.o *.html main
