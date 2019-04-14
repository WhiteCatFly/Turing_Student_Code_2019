main: main.cpp detail_parser.o html_parser.o normal_url.o
	g++ main.cpp detail_parser.o html_parser.o normal_url.o -o main 
html_parser.o: html_parser.cpp html_parser.h
	g++ -c html_parser.cpp -o html_parser.o
detail_parser.o: detail_parser.cpp html_parser.h
	g++ -c detail_parser.cpp -o detail_parser.o
normal_url.o: normal_url.cpp normal_url.h
	g++ -c normal_url.cpp -o normal_url.o
clean:
	rm -f normal_url.o detail_parser.o html_parser.o
