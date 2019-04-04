#include "Web_Crawler.h"
#include <set>
#include <queue>
#include <string>

Web_Crawler::Web_Crawler(){
	while (!url_queue.empty())
		url_queue.pop();
	url_set.clear();
	origin = current_url = current_html = "";
	total_website = successful_website = failed_website = 0;
}
