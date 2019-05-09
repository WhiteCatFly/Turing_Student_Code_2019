obj = main.o Spider.o Request.o Attribute.o Parser.o string_tools.o Tag.o


crawler: $(obj)
	g++ -o crawler $(obj) -g -pthread -Wall -std=c++11

main.o: main.cpp
	g++ -c main.cpp -g -Wall -std=c++11

Attribute.o: Attribute.h Attribute.cpp
	g++ -c Attribute.h Attribute.cpp -g -Wall -std=c++11

Parser.o: HTMLParser.h Parser.cpp
	g++ -c HTMLParser.h Parser.cpp  -g -Wall -std=c++11

string_tools.o: string_tools.h string_tools.cpp
	g++ -c string_tools.h string_tools.cpp -g -Wall -std=c++11

Request.o: Request.h Request.cpp 
	g++ -c Request.h Request.cpp -g -Wall -std=c++11

Tag.o: Tag.cpp
	g++ -c Tag.cpp -g -Wall -std=c++11

Spider.o: Spider.h Spider.cpp
	g++ -c Spider.h Spider.cpp -pthread -g -Wall -std=c++11


clean:
	rm *.o *.gch
