#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "search_engine.h"

int main(int argc, char *argv[])
{
	Search_Engine search_engine("corpus.txt");
	std::string query;
	for (; ; )
	{
		std::cout << "input a word or a phrase to search: ";
		if (!(std::cin >> query)) break;
		auto result = search_engine.search(query);
		if (result.size() == 0)
		{
			std::cout << "no pages found!\n";
		}
		else
		{
			std::cout << (int)result.size() << " pages found, top pages:\n";
			for (int i = 1; i <= std::min((int)result.size(), 10); ++i)
			{
				std::cout << i << " " << result[i - 1] << std::endl;
			}
		}
	}
	return 0;
}