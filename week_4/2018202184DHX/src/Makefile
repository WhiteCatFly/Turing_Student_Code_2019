.PHONY : clean

main : main.o HTMLParser.o HTMLParser.h
	@g++ -o HTMLParser main.o HTMLParser.o
main.o : main.cpp HTMLParser.h 
	@g++ -c main.cpp
HTMLParser.o : HTMLParser.cpp HTMLParser.h 
	@g++ -c HTMLParser.cpp
clean :
	@rm -f *.o HTMLParser