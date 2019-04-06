.PHONY : clean
main : main.o my_fetcher.o my_crawler.o my_config.o my_config.h my_fetcher.h my_crawler.h my_res.h
	@g++ -o run main.o my_fetcher.o my_crawler.o my_config.o -lcurl -lconfig++
main.o : main.cpp my_crawler.h my_fetcher.h
	@g++ -c main.cpp 
my_crawler.o : my_crawler.cpp my_crawler.h
	@g++ -c my_crawler.cpp 
my_fetcher.o : my_fetcher.cpp my_res.h my_crawler.h my_fetcher.h
	@g++ -c my_fetcher.cpp 
my_config.o : my_config.cpp my_config.h
	@g++ -c my_config.cpp  -lconfig++

clean :
	@rm -f *.o