#include <iostream>
#include <string>
#include "normalize.h"

std::string normalizing(std::string root, std::string append)
{
	root = root.substr(0, root.rfind('/'));
	append = append.substr(7);
	switch (append[0])
	{
		case '\'':
		case '\"':
		case '>':
		case ' ':
		{
			append = append.substr(1);
			break;
		}
		default:
			;
	}
	switch (append[append.length() - 1])
	{
		case '\'':
		case '\"':
		case '>':
		case ' ':
		{
			append.pop_back();
			break;
		}
		default:
			;
	}
	switch (append[0])
	{
		case '.':
		{
			if (append[1] == '/')
				append = append.substr(2);
			else if (append[1] == '.')
			{
				while (append[0] == '.' && append[1] == '.')
				{
					root = root.substr(0, root.rfind('/'));
					append = append.substr(3);
				}
			}
			break;
		}
		case '/':
		{
			int pos = root.find('/');
			while (root[pos + 1] == '/') pos = root.find('/', pos + 2);
			root = root.substr(0, pos);
			append = append.substr(1);
			break;
		}
		case 'h':
			return append;
		default:
			;
	}
	return root + "/" + append;
}