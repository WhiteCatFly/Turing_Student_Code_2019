obj = main.o Parser.o Tag.o

htmlParser: $(obj)
	g++ -o htmlParser $(obj) -g -Wall -std=c++11

main.o: main.cpp HTMLParser.h
	g++ -c main.cpp -g -Wall -std=c++11

Parser.o: Parser.cpp HTMLParser.h
	g++ -c Parser.cpp -g -Wall -std=c++11

Tag.o: Tag.cpp
	g++ -c Tag.cpp -g -Wall -std=c++11

clean:
	rm *.o
