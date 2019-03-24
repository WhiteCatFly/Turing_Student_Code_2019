objects = main.o normalizer.o\
		  href_extractor.o crawler.o

prog : $(objects)
	g++ -std=c++17 -O2 -o prog $(objects)
main.o : main.cpp
	g++ -std=c++17 -O2 -c main.cpp
normalizer.o : normalizer.cpp normalizer.h
	g++ -std=c++17 -O2 -c normalizer.cpp
href_extractor.o : href_extractor.cpp href_extractor.h
	g++ -std=c++17 -O2 -c href_extractor.cpp
crawler.o : crawler.cpp crawler.h
	g++ -std=c++17 -O2 -c crawler.cpp

clean :
	rm $(objects) prog wget-log
