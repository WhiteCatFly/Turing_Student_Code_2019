main : main.o basecrawler.o advancedcrawler.o parser.o search_engine.o
	g++ -o main main.o basecrawler.o advancedcrawler.o parser.o search_engine.o
parser.o : parser.cpp parser.h
	g++ -c parser.cpp
main.o : main.cpp
	g++ -c main.cpp
basaecrawler.o : basecrawler.cpp basecrawler.h
	g++ -c basecrawler.cpp
advancedcrawler.o : advancedcrawler.cpp advancedcrawler.h
	g++ -c advancedcrawler.cpp
search_engine.o : search_engine.cpp search_engine.h
	g++ -c search_engine.cpp
clean :
	rm main main.o basecrawler.o advancedcrawler.o parser.o search_engine.o
run :
	./main "http://info.ruc.edu.cn/" "/home/cy/Desktop/big_homework/search_engine/data/" "wget -o -t3 -T3 -O " "restart"
divide:
	./thulac -deli "/" <Chinese.txt >result_of_divide.txt