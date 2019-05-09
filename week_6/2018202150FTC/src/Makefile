claw : main.cpp claw.o parser.o
	g++ main.cpp parser.o claw.o -o claw
claw.o:claw.cpp claw.h
	g++ claw.cpp claw.h -c 
parser.o:parser.cpp claw.h
	g++ parser.cpp claw.h -c
clean:
	rm claw
	rm *.html
	rm *-log
	rm *.txt