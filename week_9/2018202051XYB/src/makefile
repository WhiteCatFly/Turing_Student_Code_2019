main : main.o Lexer.o DOM.o tagString.o Lexer.h Token.h DOM.h tagString.h Library.o Library.h Document.o Document.h search.h search.o
	@g++ -g -O0 -o run main.o Library.o Document.o search.o DOM.o Lexer.o tagString.o 
main.o : main.cpp
	@g++ -g -O0 -c main.cpp
Lexer.o : Lexer.cpp Lexer.h Token.h tagString.h
	@g++ -g -O0 -c Lexer.cpp
DOM.o : DOM.cpp DOM.h Token.h tagString.h Lexer.h
	@g++ -g -O0 -c DOM.cpp
tagString.o : tagString.cpp tagString.h
	@g++ -g -O0 -c tagString.cpp
Document.o : Document.cpp Document.h search.h search.cpp
	@g++ -g -O0 -c Document.cpp
Library.o : Library.cpp Library.h Document.cpp Document.h search.h search.cpp Lexer.h Token.h tagString.h DOM.h
	@g++ -g -O0 -c Library.cpp
search.o : search.h search.cpp
	@g++ -g -O0 -c search.cpp
clean :
	@rm -f *.o