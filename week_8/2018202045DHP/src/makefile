SE : IW main2.cpp search_engine.h fundamental_search_engine.o
	g++ -o SE main2.cpp fundamental_search_engine.o
fundamental_search_engine.o : search_engine.h fundamental_search_engine.cpp
	g++ -c fundamental_search_engine.cpp

IW : main.cpp internetworm.h htmlparser.h fundamental_URL.o format_URL.o extract_HtmlParser.o fundamental_HtmlParser.o loader.o saver.o
	g++ -o IW main.cpp fundamental_URL.o format_URL.o extract_HtmlParser.o fundamental_HtmlParser.o loader.o saver.o
fundamental_URL.o : fundamental_URL.cpp internetworm.h
	g++ -c fundamental_URL.cpp
format_URL.o : format_URL.cpp internetworm.h
	g++ -c format_URL.cpp
fundamental_HtmlParser.o : fundamental_HtmlParser.cpp htmlparser.h internetworm.h
	g++ -c fundamental_HtmlParser.cpp
extract_HtmlParser.o : extract_HtmlParser.cpp htmlparser.h internetworm.h
	g++ -c extract_HtmlParser.cpp
loader.o : loader.cpp internetworm.h
	g++ -c loader.cpp
saver.o : saver.cpp internetworm.h
	g++ -c saver.cpp

clean :
	rm -rf IW fundamental_URL.o format_URL.o fundamental_HtmlParser.o extract_HtmlParser.o loader.o saver.o
