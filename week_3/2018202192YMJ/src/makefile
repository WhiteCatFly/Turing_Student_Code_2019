objects = main.o crawler.o normalizer.o\
		  url_utility.o href_extractor.o

prog : $(objects)
	g++ -std=c++17 -O2 -o prog $(objects)
main.o : main.cpp
	g++ -std=c++17 -O2 -c main.cpp
crawler.o : crawler.cpp crawler.h
	g++ -std=c++17 -O2 -c crawler.cpp
normalizer.o : normalizer.cpp normalizer.h
	g++ -std=c++17 -O2 -c normalizer.cpp
url_utility.o : url_utility.cpp url_utility.h
	g++ -std=c++17 -O2 -c url_utility.cpp
href_extractor.o : href_extractor.cpp href_extractor.h
	g++ -std=c++17 -O2 -c href_extractor.cpp

clean :
	rm $(objects) prog wget-log
