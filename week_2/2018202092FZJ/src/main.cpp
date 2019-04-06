#include "web_crawler.h"
#include <iostream>
#include <ctime>

int main(){
	clock_t now = clock();
	bfs();
	int times = (clock() - now) / 1000;
	std::cout << times / 60 << "m" << times % 60 << std::endl;
	return 0;
}