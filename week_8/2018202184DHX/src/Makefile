.PHONY : clean

main : main.o Query.o Query.h
	@g++ -o Query main.o Query.o
main.o : main.cpp Query.h
	@g++ -c main.cpp
Query.o : Query.h Query.cpp
	@g++ -c Query.cpp
clean :
	@rm -f *.o Query