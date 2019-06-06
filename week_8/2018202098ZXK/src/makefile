obj = search.o  TermLog.o vec_uti.o


prog: $(obj)
	g++ -o prog $(obj) -g -pthread -Wall -std=c++11

TermLog.o: TermLog.cpp  TermLog.h
	g++ -c TermLog.cpp  TermLog.h -g -Wall -std=c++11

vec_uti.o: vec_uti.cpp  vec_uti.h
	g++ -c vec_uti.cpp  vec_uti.h -g -Wall -std=c++11

search.o: search.cpp
	g++ -c search.cpp -g -Wall -std=c++11

clean:
	rm *.o *.gch
