IW : main.cpp internetworm.h extracter.o filter.o loader.o
	g++ -o IW main.cpp extracter.o filter.o loader.o
extracter.o : extracter.cpp
	g++ -c extracter.cpp
filter.o : filter.cpp
	g++ -c filter.cpp
loader.o : loader.cpp
	g++ -c loader.cpp
clean :
	rm -rf extracter.o filter.o loader.o IW
