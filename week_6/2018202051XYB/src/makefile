.PHONY : clean
main : main.o Fetcher.o Crawler.o Config.o Config.h Fetcher.h Crawler.h res.h Lexer.o DOM.o tagString.o Lexer.h Token.h DOM.h tagString.h
	@g++ -o run main.o Fetcher.o Crawler.o Config.o DOM.o Lexer.o tagString.o -lcurl -lconfig++
main.o : main.cpp Crawler.h Fetcher.h
	@g++ -c main.cpp 
Crawler.o : Crawler.cpp Crawler.h DOM.h
	@g++ -c Crawler.cpp 
Fetcher.o : Fetcher.cpp res.h Crawler.h Fetcher.h
	@g++ -c Fetcher.cpp 
Config.o : Config.cpp Config.h
	@g++ -c Config.cpp  -lconfig++

Lexer.o : Lexer.cpp Lexer.h Token.h tagString.h
	@g++ -c Lexer.cpp
DOM.o : DOM.cpp DOM.h Token.h tagString.h Lexer.h
	@g++ -c DOM.cpp
tagString.o : tagString.cpp tagString.h
	@g++ -c tagString.cpp

clean :
	@rm -f *.o