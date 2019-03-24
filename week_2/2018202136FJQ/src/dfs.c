#include "BigJob.h"

void deep_search(void)
{
        while(!url_to_be_crawled.empty())
        {
                current_url = url_to_be_crawled.front();
                url_to_be_crawled.pop();
                if(url_already_be_crawled.find(current_url) == url_already_be_crawled.end())
                {
                        number++;
                        getContent(current_url);
                }
                url_already_be_crawled.insert(current_url);
        }
	cout << number << endl;
}
