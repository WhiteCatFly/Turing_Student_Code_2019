objects = main.o spiderWeb.o spiderFile.o spiderString.o

prog : $(objects)
	g++ -std=c++17 -O2 -o prog $(objects) -pthread

main.o : main.cpp spiderString.h spiderFile.h spiderWeb.h 
	g++ -std=c++17 -O2 -c -pthread main.cpp spiderString.h spiderFile.h spiderWeb.h
spiderWeb.o : spiderWeb.cpp spiderWeb.h
	g++ -std=c++17 -O2 -c spiderWeb.cpp spiderWeb.h
spiderFile.o : spiderFile.cpp spiderFile.h
	g++ -std=c++17 -O2 -c spiderFile.cpp spiderFile.h
spiderString.o : spiderString.cpp spiderString.h
	g++ -std=c++17 -O2 -c spiderString.cpp spiderString.h


clean :
	rm $(objects) wget-log