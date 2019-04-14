HP: htmlparser.h main.cpp element_support.o download.o mainbodyanalyzer.o
	g++ -o HP main.cpp element_support.o download.o mainbodyanalyzer.o
element_support.o: htmlparser.h element_support.cpp
	g++ -c element_support.cpp
download.o: htmlparser.h download.cpp
	g++ -c download.cpp
mainbodyanalyzer.o: htmlparser.h mainbodyanalyzer.cpp
	g++ -c mainbodyanalyzer.cpp
clean:
	rm -rf element_support.o download.o mainbodyanalyzer.o HP