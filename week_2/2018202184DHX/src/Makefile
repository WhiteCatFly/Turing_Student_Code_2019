.PHONY : clean

main : main.o bfs.o UrlToString.o StringOperate.o bfs.h UrlToString.h StringOperate.h
	@g++ -o web_crawl main.o bfs.o UrlToString.o StringOperate.o
main.o : main.cpp bfs.h 
	@g++ -c main.cpp
StringOperate.o : StringOperate.cpp bfs.h StringOperate.h
	@g++ -c StringOperate.cpp
UrlToString.o : UrlToString.cpp bfs.h UrlToString.h
	@g++ -c UrlToString.cpp
bfs.o : bfs.cpp bfs.h StringOperate.h UrlToString.h
	@g++ -c bfs.cpp
clean :
	@rm -f *.o 