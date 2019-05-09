main : main.o basecrawler.o advancedcrawler.o parser.o
	g++ -o main main.o basecrawler.o advancedcrawler.o parser.o
parser.o : parser.cpp parser.h
	g++ -c parser.cpp
main.o : main.cpp
	g++ -c main.cpp
basaecrawler.o : basecrawler.cpp basecrawler.h
	g++ -c basecrawler.cpp
advancedcrawler.o : advancedcrawler.cpp advancedcrawler.h
	g++ -c advancedcrawler.cpp
clean :
	rm main main.o basecrawler.o advancedcrawler.o parser.o
run :
	./main "http://info.ruc.edu.cn/" "/home/cy/Desktop/big_homework/midterm/data/" "wget -o -t3 -T3 -O " "continue"