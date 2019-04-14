main : main.o Lexer.o DOM.o tagString.o Lexer.h Token.h DOM.h tagString.h
	@g++ -o run main.o DOM.o Lexer.o tagString.o
main.o : main.cpp Lexer.h Token.h tagString.h DOM.h
	@g++ -c main.cpp
Lexer.o : Lexer.cpp Lexer.h Token.h tagString.h
	@g++ -c Lexer.cpp
DOM.o : DOM.cpp DOM.h Token.h tagString.h Lexer.h
	@g++ -c DOM.cpp
tagString.o : tagString.cpp tagString.h
	@g++ -c tagString.cpp
clean :
	@rm -f *.o