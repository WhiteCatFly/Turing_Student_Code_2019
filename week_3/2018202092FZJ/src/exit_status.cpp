#include "Web_Crawler.h"
#include <cstdio>

void Web_Crawler::exit_status(int res){
	switch (res){
		case 0:{
			++successful_website;
			break;
		}
		case 1:{
			printf("Generic error code.\n");
			++failed_website;
		}
		case 2:{
			printf("Parse error—for instance, when parsing command-line options, the ‘.wgetrc’ or ‘.netrc’...\n");
			++failed_website;
		}
		case 3:{
			printf("File I/O error.\n");
			++failed_website;
		}
		case 4:{
			printf("Network failure.\n");
			++failed_website;
		}
		case 5:{
			printf("SSL verification failure.\n");
			++failed_website;
		}
		case 6:{
			printf("Username/password authentication failure.\n");
			++failed_website;
		}
		case 7:{
			printf("Protocol errors.\n");
			++failed_website;
		}
		case 8:{
			printf("Server issued an error response.\n");
			++failed_website;
		}
		default:{
			printf("Fail to crawl website.\n");
			++failed_website;
		}
	}
}
