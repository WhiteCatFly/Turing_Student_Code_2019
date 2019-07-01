exec : (Neutralized)main_control.cpp searchengine.o document.o field.o stringfield.o numberfield.o datefield.o valuation.o
	g++ -o exec \(Neutralized\)main_control.cpp searchengine.o document.o field.o stringfield.o numberfield.o datefield.o valuation.o
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
valuation.o : valuation.cpp valuation.h numberfield.h stringfield.h datefield.h
	g++ -c valuation.cpp
searchengine.o : searchengine.cpp searchengine.h field.h document.h valuation.h
	g++ -c searchengine.cpp
clear :
	rm -rf field.o numberfield.o stringfield.o datefield.o document.o valuation.o searchengine.o exec
