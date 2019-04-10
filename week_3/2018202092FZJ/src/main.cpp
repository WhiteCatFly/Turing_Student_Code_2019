#include "Web_Crawler.h"
#include <cstdio>
#include <cstdlib>

int main(int argc ,char* argv[]){
	if (argc == 1)
		printf("Please input the website you need to crawl.\n");
	else if (argc > 2)
			printf("Please input only one website at a time.\n");
		else {
			system("rm *.html");
			system("reset");
			Web_Crawler run;
			run.Web_Crawler_BFS(argv[1]);
		}
	return 0;
}
