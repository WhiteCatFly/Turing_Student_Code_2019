.PHNOY:clean

main:main.cpp head.h HTMLparser.o extract.o else.o
	g++ -o main main.cpp HTMLparser.o extract.o else.o

HTMLparser.o: HTMLparser.cpp
	g++ -c HTMLparser.cpp

extract.o: extract.cpp
	g++ -c extract.cpp

else.o:else.cpp
	g++ -c else.cpp

clean:
	-rm *.o file.html main