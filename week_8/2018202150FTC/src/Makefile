search: main.cpp parser.o search.o
	g++ main.cpp parser.o search.o -o search
parser.o:parser.cpp parser.h
	g++ parser.cpp parser.h -c
search.o:search.cpp parser.h search.h
	g++ search.cpp parser.h search.h -c
