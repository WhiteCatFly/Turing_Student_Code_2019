all : main.cpp htmlParser_get.o htmlParser_initialize.o parse.o unit.h parser_getcontent.o parser_init.o parser_bfs.o
	g++ -o all main.cpp htmlParser_get.o htmlParser_initialize.o parse.o unit.h parser_getcontent.o parser_init.o parser_bfs.o
htmlParser_get.o : htmlParser_get.cpp
	g++ -c htmlParser_get.cpp
htmlParser_initialize.o : htmlParser_initialize.cpp
	g++ -c htmlParser_initialize.cpp
parse.o : parse.cpp
	g++ -c parse.cpp
parser_getcontent.o : parser_getcontent.cpp
	g++ -c parser_getcontent.cpp
parser_init.o : parser_init.cpp
	g++ -c parser_init.cpp
parser_bfs.o : parser_bfs.cpp
	g++ -c parser_bfs.cpp

clean : 
		rm *.o all
