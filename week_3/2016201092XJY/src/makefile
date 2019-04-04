edit: main.o webpage.o
	g++ -std=c++11 main.cpp webpage.cpp -o edit

main.o: main.cpp webpage.h
	g++ -std=c++11 -c main.cpp -o main.o

webpage.o: webpage.cpp webpage.h
	g++ -std=c++11 -c webpage.cpp -o webpage.o

clean: 
	rm edit webpage.o

