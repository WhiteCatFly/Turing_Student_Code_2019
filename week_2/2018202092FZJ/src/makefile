web_crawler :main.o bfs.o get_html.o find_next_url.o
	g++ -o web_crawler main.o bfs.o get_html.o find_next_url.o 

main.o : main.cpp bfs.cpp web_crawler.h
	g++ main.cpp -c -Wall

bfs.o : bfs.cpp get_html.cpp find_next_url.cpp web_crawler.h
	g++ bfs.cpp -c -Wall
	
get_html.o : get_html.cpp web_crawler.h
	g++ get_html.cpp -c -Wall
	
find_next_url.o : find_next_url.cpp web_crawler.h
	g++ find_next_url.cpp -c -Wall

clean :
	rm *.o
	

