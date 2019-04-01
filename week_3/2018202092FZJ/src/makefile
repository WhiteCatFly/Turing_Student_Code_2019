Web_Crawler :main.o Web_Crawler_BFS.o get_html.o parse_html.o exit_status.o initialization.o
	g++ -o Web_Crawler main.o Web_Crawler_BFS.o get_html.o parse_html.o exit_status.o initialization.o

main.o : main.cpp Web_Crawler_BFS.cpp Web_Crawler.h
	g++ main.cpp -c -Wall

Web_Crawler_BFS.o : Web_Crawler_BFS.cpp get_html.cpp parse_html.cpp Web_Crawler.h
	g++ Web_Crawler_BFS.cpp -c -Wall
	
get_html.o : get_html.cpp Web_Crawler.h
	g++ get_html.cpp -c -Wall
	
parse_html.o : parse_html.cpp Web_Crawler.h
	g++ parse_html.cpp -c -Wall
	
exit_status.o : exit_status.cpp Web_Crawler.h
	g++ exit_status.cpp -c -Wall

initialization.o : initialization.cpp Web_Crawler.h
	g++ initialization.cpp -c -Wall

clean :
	rm *.o
	

