#include <cmath>
#include <cassert>

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "search_engine.h"
#include "THULAC_lite_c++_v1/include/thulac.h"

std::ostream & operator << (std::ostream &os, const Search_Result &result)
{
	os << result.m_tf_idf << " " << result.m_title << " " << result.m_url << " " << result.m_context;
	return os;
}

Search_Engine::Search_Engine(const std::string file_name)
{
	std::ifstream fin(file_name);
	if(fin.is_open())
	{
		unsigned int num_of_lines;
		std::string title, url;
		for (int page_id = 0; fin >> title >> url >> num_of_lines; ++page_id)
		{
			std::vector<std::vector<std::string>> contents;
			for (int line_id = 0; line_id < num_of_lines; ++line_id)
			{
				std::string line, word;
				std::vector<std::string> list_words;
				if (line_id == 0) getline(fin, line);
				getline(fin, line);
				std::istringstream isstrm(line);
				for (int word_id = 0; ; ++word_id)
				{
					isstrm >> word;
					if (!isstrm) break;
					list_words.push_back(word);
					m_list[word][page_id][line_id].push_back(word_id);
				}
				contents.push_back(list_words);
			}
			m_pages.push_back(Page(title, url, contents));
		}
		fin.close();
	}
	else
	{
		std::cerr << "fatal error: cannot open file \"" << file_name << "\"\n";
		exit(1);
	}
}

std::vector<Search_Result> Search_Engine::search(const std::string &query)
{
	static THULAC thulac;
	static bool first_invocation = true;
	std::vector<Search_Result> result;
	if (first_invocation)
	{
		thulac.init("models/", NULL, true);
		first_invocation = false;
	}
	THULAC_result thulac_result;
	thulac.cut(query, thulac_result);
	std::vector<std::string> query_segmentation;
	for (int i = 0; i < (int)thulac_result.size() - 1; ++i)
	{
		query_segmentation.push_back(thulac_result[i].first);
	}
	int num_of_query_words = (int)query_segmentation.size();
	std::vector<double> idf;
	idf.resize(num_of_query_words);
	for (int i = 0; i < num_of_query_words; ++i)
	{
		idf[i] = log((double)m_pages.size() / m_list[query_segmentation[i]].size());
	}
	for (auto page_id: m_list[query_segmentation[0]])
	{
		std::vector<double> tf;
		tf.resize(num_of_query_words);
		for (int i = 0; i < num_of_query_words; ++i)
		{
			for (auto line_id: m_list[query_segmentation[i]][page_id.first])
			{
				tf[i] += (int)(line_id.second).size();
			}
			if (m_pages[page_id.first].m_title.find(query_segmentation[i]) != std::string::npos)
			{
				tf[i] += (int)m_pages[page_id.first].m_contents.size();
			}
			tf[i] = 1 + log(tf[i]);
		}
		double sigma_tf_idf = 0;
		for (int i = 0; i < num_of_query_words; ++i)
		{
			sigma_tf_idf += tf[i] * idf[i];
		}
		bool page_match = false;
		std::string context;
		for (auto line_id: page_id.second)
		{
			if (page_match) break;
			for (auto word_id: line_id.second)
			{
				bool match = true;
				if(page_match) break;
				for (int i = 1; i < num_of_query_words; ++i)
				{
					if (word_id + i >= (int)m_pages[page_id.first].m_contents[line_id.first].size()
						|| m_pages[page_id.first].m_contents[line_id.first][word_id + i] != query_segmentation[i])
					{
						match = false;
						break;
					}
				}
				if (match)
				{
					page_match = true;
					for (auto word: m_pages[page_id.first].m_contents[line_id.first])
					{
						context += word;
					}
				}
			}
		}
		if (page_match)
		{
			result.push_back(Search_Result(sigma_tf_idf,
										   m_pages[page_id.first].m_title,
										   m_pages[page_id.first].m_url,
										   context));
		}
	}
	std::sort(result.begin(), result.end());
	return result;
}
