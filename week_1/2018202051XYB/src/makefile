.PHONY : clean

main : main.o my_string.o my_curl.o main.h my_string.h my_curl.h
	@g++ -o run main.o my_string.o my_curl.o -lcurl
main.o : main.cpp main.h my_string.h my_curl.h
	@g++ -c main.cpp
my_string.o : my_string.cpp main.h my_string.h
	@g++ -c my_string.cpp
my_curl.o : my_curl.cpp main.h my_string.h my_curl.h
	@g++ -c my_curl.cpp
clean :
	@rm -f *.o