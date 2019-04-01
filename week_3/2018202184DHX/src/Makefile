.PHONY : clean

main : main.o Crawler.o Crawler.h
	@g++ -o web_crawl main.o Crawler.o
main.o : main.cpp Crawler.h
	@g++ -c main.cpp
Crawler.o : Crawler.h
	@g++ -c Crawler.cpp
clean:
	@rm -f *.o
	@rm -f test *.html