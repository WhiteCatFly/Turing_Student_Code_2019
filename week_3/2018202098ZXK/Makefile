objects = main.o string_tools.o Request.o 

prog : $(objects)
	g++ -std=c++17 -O2 -o prog $(objects) -pthread

main.o : main.cpp string_tools.h Request.h
	g++ -std=c++17 -O2 -c -pthread main.cpp string_tools.h Request.h
string_tools.o : string_tools.cpp string_tools.h
	g++ -std=c++17 -O2 -c string_tools.cpp string_tools.h
Request.o : Request.cpp Request.h
	g++ -std=c++17 -O2 -c Request.cpp Request.h
clean: $(objects)
	rm -f wget-log $(objects)