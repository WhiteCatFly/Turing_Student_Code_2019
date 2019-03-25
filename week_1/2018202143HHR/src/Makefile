crawler: AsyncRequestPool.o Crawler.o UrlParser.o
	g++-8 -std=c++17 AsyncRequestPool.o Crawler.o UrlParser.o -o crawler -O2 -lstdc++fs
UrlParser.o: UrlParser.cc UrlParser.h
	g++-8 -std=c++17 -c UrlParser.cc -o UrlParser.o -O2
AsyncRequestPool.o: AsyncRequestPool.cc AsyncRequestPool.h Config.h
	g++-8 -std=c++17 -c AsyncRequestPool.cc -o AsyncRequestPool.o -O2
Crawler.o: Crawler.cc TerminalColor.h UrlParser.h AsyncRequestPool.h
	g++-8 -std=c++17 -c Crawler.cc -o Crawler.o -O2
test.o: test.cc AsyncRequestPool.h
	g++-8 -std=c++17 -c test.cc -o test.o -O2
test: AsyncRequestPool.o test.o
	g++-8 -std=c++17 AsyncRequestPool.o test.o -o test -O2
clean:
	rm -f crawler UrlParser.o AsyncRequestPool.o Crawler.o test.o test
