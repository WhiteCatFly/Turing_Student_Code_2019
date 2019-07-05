exec : (Neutralized)main_control.cpp searchengine.o document.o field.o stringfield.o numberfield.o datefield.o BM25_valuator.o
	g++ -o exec \(Neutralized\)main_control.cpp searchengine.o document.o field.o stringfield.o numberfield.o datefield.o BM25_valuator.o
field.o : field.cpp field.h
	g++ -c field.cpp
numberfield.o : numberfield.cpp numberfield.h
	g++ -c numberfield.cpp
stringfield.o : stringfield.cpp stringfield.h
	g++ -c stringfield.cpp
datefield.o : datefield.cpp datefield.h
	g++ -c datefield.cpp
document.o : document.cpp document.h field.h
	g++ -c document.cpp
searchengine.o : searchengine.cpp searchengine.h field.h document.h BM25_valuator.h
	g++ -c searchengine.cpp
BM25_valuator.o : BM25_valuator.cpp BM25_valuator.h
	g++ -c BM25_valuator.cpp
clear :
	rm -rf field.o numberfield.o stringfield.o datefield.o document.o valuation.o searchengine.o BM25_valuator.o exec
