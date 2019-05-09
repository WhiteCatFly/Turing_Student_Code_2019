.PHONY : clean

main : main.o HTMLParser.o HTMLParser.h Crawler.o Crawler.h
	@g++ -o Final_Crawler main.o HTMLParser.o Crawler.o
main.o : main.cpp HTMLParser.h Crawler.h
	@g++ -c main.cpp
HTMLParser.o : HTMLParser.cpp HTMLParser.h 
	@g++ -c HTMLParser.cpp
Crawler.o : Crawler.cpp Crawler.h
	@g++ -c Crawler.cpp
clean :
	@rm -f *.o Final_Crawler