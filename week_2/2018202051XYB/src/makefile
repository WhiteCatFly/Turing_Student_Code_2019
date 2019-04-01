.PHONY : clean

main : main.o my_string.o my_curl.o bfs.o bfs.h my_string.h my_curl.h
	@g++ -o run main.o my_string.o my_curl.o bfs.o -lcurl
main.o : main.cpp bfs.h 
	@g++ -c main.cpp
my_string.o : my_string.cpp bfs.h my_string.h
	@g++ -c my_string.cpp
my_curl.o : my_curl.cpp bfs.h my_string.h my_curl.h
	@g++ -c my_curl.cpp
bfs.o : bfs.cpp bfs.h my_string.h my_curl.h
	@g++ -c bfs.cpp
clean :
	@rm -f *.o