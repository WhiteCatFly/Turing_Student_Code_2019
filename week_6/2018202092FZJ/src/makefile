crawler : main.o bfs.o getcontent.o init.o extract.o parse.o parser.o 
	g++ -o crawler main.o bfs.o getcontent.o init.o extract.o parse.o parser.o 

main.o : main.cpp crawler.h
	g++ main.cpp -c -Wall

bfs.o : bfs.cpp crawler.h
	g++ bfs.cpp -c -Wall

extract.o : extract.cpp crawler.h
	g++ extract.cpp -c -Wall

getcontent.o : getcontent.cpp crawler.h
	g++ getcontent.cpp -c -Wall

init.o : init.cpp crawler.h
	g++ init.cpp -c -Wall

parse.o : parse.cpp crawler.h
	g++ parse.cpp -c -Wall

parser.o : parser.cpp crawler.h
	g++ parser.cpp -c -Wall

clean :
	rm *.o
