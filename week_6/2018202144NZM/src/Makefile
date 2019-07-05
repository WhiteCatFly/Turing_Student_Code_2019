main: main.cpp detail_parser.o html_parser.o normal_url.o get_source.o console_analyzer.o
	g++ main.cpp detail_parser.o html_parser.o normal_url.o get_source.o console_analyzer.o -o main 
console_analyzer.o: console_analyzer.cpp console_analyzer.h detail_parser.o html_parser.o normal_url.o get_source.o
	g++ -c console_analyzer.cpp -o console_analyzer.o
html_parser.o: html_parser.cpp html_parser.h
	g++ -c html_parser.cpp -o html_parser.o
detail_parser.o: detail_parser.cpp detail_parser.h html_parser.h 
	g++ -c detail_parser.cpp -o detail_parser.o
normal_url.o: normal_url.cpp normal_url.h
	g++ -c normal_url.cpp -o normal_url.o
get_source.o: get_source.cpp normal_url.h
	g++ -c get_source.cpp -o get_source.o
clean:
	rm -f normal_url.o detail_parser.o html_parser.o get_source.o console_analyzer.o
