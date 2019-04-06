pro : main.cpp total.h format_bool.o url_bool.o minitofull.o
	g++ -o pro main.cpp format_bool.o url_bool.o minitofull.o -std=c++11
format_bool.o : format_bool.cpp
	g++ -c format_bool.cpp
url_bool.o : url_bool.cpp
	g++ -c url_bool.cpp
minitofull.o : minitofull.cpp
	g++ -c minitofull.cpp
clean :
	rm -rf format_bool.o url_bool.o minitofull.o pro
