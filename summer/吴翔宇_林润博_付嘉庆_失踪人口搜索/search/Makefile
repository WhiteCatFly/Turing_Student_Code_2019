bighomework.cgi : bighomework main.o Query.o itoa.o store.o Similarity.o TopResult.o utf8change.o PersonData.o Scorer.o main.cpp Query.cpp itoa.cpp store.cpp Similarity.cpp TopResult.cpp utf8change.cpp PersonData.cpp Scorer.cpp
	g++ -o bighomework.cgi main.o Query.o itoa.o store.o Similarity.o TopResult.o utf8change.o PersonData.o Scorer.o -std=c++11
bighomework : main.o Query.o itoa.o store.o Similarity.o TopResult.o utf8change.o PersonData.o Scorer.o main.cpp Query.cpp itoa.cpp store.cpp Similarity.cpp TopResult.cpp utf8change.cpp PersonData.cpp Scorer.cpp
	g++ -o bighomework main.o Query.o itoa.o store.o Similarity.o TopResult.o utf8change.o PersonData.o Scorer.o -std=c++11
main.o : main.cpp PersonData.h
	g++ -c main.cpp
Query.o : Query.cpp Query.h utf8change.h
	g++ -c Query.cpp
itoa.o : itoa.cpp  PersonData.h
	g++ -c itoa.cpp
store.o : store.cpp Similarity.h PersonData.h
	g++ -c store.cpp
Similarity.o : Similarity.cpp PersonData.h
	g++ -c Similarity.cpp 
TopResult.o : TopResult.cpp PersonData.h
	g++ -c TopResult.cpp
utf8change.o : utf8change.cpp
	g++ -c utf8change.cpp
PersonData.o : PersonData.cpp PersonData.h
	g++ -c Persondata.cpp
Scorer.o : Scorer.cpp Similarity.h
	g++ -c Scorer.cpp