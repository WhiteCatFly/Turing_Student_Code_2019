pro : main.cpp caculate.o BigInteger.o
	g++ -o pro main.cpp caculate.o BigInteger.o
caculate.o : caculate.cpp
	g++ -c caculate.cpp
BigInteger.o : BigInteger.cpp
	g++ -c BigInteger.cpp
clean : 
	rm -rf pro caculate.o BigInteger.o