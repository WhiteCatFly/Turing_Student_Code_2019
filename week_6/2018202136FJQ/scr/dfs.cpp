#include "head.h"

void Crawled::deep_search(void)
{
	url_to_be_Crawled.push(_root);
        while(!url_to_be_Crawled.empty())
        {
                current_url = url_to_be_Crawled.front();
                url_to_be_Crawled.pop();
                if(url_already_be_Crawled.find(current_url) == url_already_be_Crawled.end())
                {
                        number++;
                        getContent(current_url);
                }
                url_already_be_Crawled.insert(current_url);
        }
	cout << "The number of urls :"<< number << endl;
}
