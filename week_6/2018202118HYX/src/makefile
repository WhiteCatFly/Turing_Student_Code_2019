.PHNOY:clean

main:main.cpp head.h Get.o Base.o Parser.o EI.o command.o
	g++ -o main main.cpp Get.o Base.o Parser.o	EI.o command.o

Get.o: Get.cpp
	g++ -c Get.cpp

Base.o: Base.cpp
	g++ -c Base.cpp

Parser.o: Parser.cpp
	g++ -c Parser.cpp

EI.o: EI.cpp
	g++ -c EI.cpp

command.o:command.cpp
	g++ -c command.cpp

clean:
	-rm *.o main *.html