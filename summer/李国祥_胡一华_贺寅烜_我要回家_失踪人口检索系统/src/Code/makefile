all.exe :main.cpp  Date.o Date.h Person.o Query.o QueryResult.o Score.o Statistics.o Base.o
		g++ -o all main.cpp  Person.o Query.o Base.o Date.o Statistics.o QueryResult.o Score.o
Base.o : Base.cpp Base.h Date.h Query.h Score.h Person.h Statistics.h QueryResult.h
		g++ -c Base.cpp 
Person.o : Person.cpp Person.h Date.h
		g++ -c Person.cpp 
Date.o : Date.cpp Date.h
		g++ -c Date.cpp
Statistics.o : Statistics.cpp Statistics.h Person.h Date.h
		g++ -c Statistics.cpp
Query.o : Query.cpp Query.h Date.h
		g++ -c Query.cpp
QueryResult.o : QueryResult.cpp QueryResult.h Base.h
		g++ -c QueryResult.cpp
Score.o : Score.cpp Score.h QueryResult.h
		g++ -c Score.cpp
clean :
		rm -rf *.o