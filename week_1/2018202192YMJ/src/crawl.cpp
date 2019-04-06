#include <cstdlib>

#include <string>
#include <iostream>

std::string get_file_name(std::string url)
{
	std::string file_name;
	file_name = "pages/";
	for (auto i = url.find("/") + 1; i < url.size(); ++i)
	{
		if (url[i] == '/')
		{
			file_name += "__";
		}
		else
		{
			file_name += url[i];
		}
	}
	return file_name;
}

std::string get_cmd(std::string file_name, std::string url)
{
	std::string cmd = "wget -o wget-log -t3 -T3 -O ";
	for (auto c: file_name)
	{
		if (c == '&') cmd += '\\';
		cmd += c;
	}
	cmd += " ";
	for (auto c: url)
	{
		if (c == '&') cmd += '\\';
		cmd += c;
	}
	return cmd;
}

std::string crawl(std::string url)
{
	extern std::string homepage;
	auto file_name = get_file_name(url);
	auto cmd = get_cmd(file_name, url);
	if (system(cmd.c_str()))
	{
		std::cerr << "error: wget failed" << "\n";
		std::cerr << "error command: " << cmd << "\n";
	}
	return file_name;
}
