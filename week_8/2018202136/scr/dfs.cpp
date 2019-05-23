#include "head.h"

void HtmlParser::deep_search(void)
{
	url_to_be_HtmlParser.push(_root);
        while(!url_to_be_HtmlParser.empty())
        {
                current_url = url_to_be_HtmlParser.front();
                url_to_be_HtmlParser.pop();
                if(url_already_be_HtmlParser.find(current_url) == url_already_be_HtmlParser.end())
                {
                        number++;
                        getContent(current_url);
                }
                url_already_be_HtmlParser.insert(current_url);
        }
	cout << "The number of urls :"<< number << endl;
}
