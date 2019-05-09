objects = main.o crawler.o normalizer.o \
		  url_utility.o html_parser.o string_utility.o

prog: $(objects)
	g++ -std=c++17 -O2 -o prog $(objects)
main.o: main.cpp crawler.h normalizer.h url_utility.h  html_parser.h string_utility.h
	g++ -std=c++17 -O2 -c main.cpp
crawler.o : crawler.cpp crawler.h normalizer.h url_utility.h html_parser.h
	g++ -std=c++17 -O2 -c crawler.cpp
normalizer.o : normalizer.cpp normalizer.h url_utility.h
	g++ -std=c++17 -O2 -c normalizer.cpp
url_utility.o : url_utility.cpp url_utility.h 
	g++ -std=c++17 -O2 -c url_utility.cpp
html_parser.o : html_parser.cpp html_parser.h normalizer.h url_utility.h string_utility.h
	g++ -std=c++17 -O2 -c html_parser.cpp
string_utility.o: string_utility.cpp string_utility.h
	g++ -std=c++17 -O2 -c string_utility.cpp

clean:
	rm $(objects)
