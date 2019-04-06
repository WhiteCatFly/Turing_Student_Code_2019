main : main.o crawler.o url_string.o others.o
	g++ -o main main.o others.o url_string.o crawler.o 
main.o : main.cpp
	g++ -c main.cpp
crawler.o : crawler.cpp others.o url_string.o
	g++ -c crawler.cpp
url_string.o : url_string.cpp
	g++ -c url_string.cpp
others.o : others.cpp
	g++ -c others.cpp
clean :
	rm main main.o crawler.o url_string.o others.o
run :
	./main "http://econ.ruc.edu.cn/" "/home/cy/Desktop/big_homework/crawler2/data/"