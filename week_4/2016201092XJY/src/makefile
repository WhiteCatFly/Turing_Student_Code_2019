edit: main.o HTMLParser.o DOMTree.o node.o
	g++ -std=c++11 main.cpp HTMLParser.cpp DOMTree.cpp node.cpp -o edit

main.o: main.cpp HTMLParser.h DOMTree.h
	g++ -std=c++11 -c main.cpp -o main.o

HTMLParser.o: HTMLParser.cpp HTMLParser.h
	g++ -std=c++11 -c HTMLParser.cpp -o HTMLParser.o

DOMTree.o: DOMTree.cpp DOMTree.h node.h
	g++ -std=c++11 -c DOMTree.cpp -o DOMTree.o

node.o: node.cpp node.h
	g++ -std=c++11 -c node.cpp -o node.o

clean:
	rm edit main.o HTMLParser.o
