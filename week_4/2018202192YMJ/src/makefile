objects = main.o html_parser.o node.o\
          attribute.o token.o string_utility.o 

prog: $(objects)
          g++ -std=c++17 -O2 -o prog $(objects)
main.o: main.cpp string_utility.h token.h attribute.h node.h html_parser.h
          g++ -std=c++17 -O2 -c main.cpp
html_parser.o: html_parser.cpp string_utility.h token.h attribute.h node.h html_parser.h
          g++ -std=c++17 -O2 -c html_parser.cpp
node.o: node.cpp string_utility.h token.h attribute.h node.h
          g++ -std=c++17 -O2 -c node.cpp
attribute.o: attribute.cpp string_utility.h token.h attribute.h
          g++ -std=c++17 -O2 -c attribute.cpp
token.o: token.cpp string_utility.h token.h
          g++ -std=c++17 -O2 -c token.cpp
string_utility.o: string_utility.cpp string_utility.h
          g++ -std=c++17 -O2 -c string_utility.cpp

clean:
          rm $(objects)
