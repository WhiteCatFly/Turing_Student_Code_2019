#include <iostream>
#include <string>
#include "normalize.h"

std::string normalizing(std::string root, std::string append, int type)
{
	if (root.find('.') > root.find('/')) root += "/";
	if (type <= 2)
	{
		while (append.find('>') != -1)
		{
			append = append.substr(append.find('>') + 1);
			append = append.substr(0, append.rfind('<'));
		}
		return append;
	}
	else if (type == 3)
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
	else return append;
}

std::string filename(std::string name)
{
	int tmp = name.find('.');
	while (tmp != name.npos)
	{
		name[tmp] = '_';
		tmp = name.find('.');
	}
	tmp = name.find('/');
	while (tmp != name.npos)
	{
		name[tmp] = '_';
		tmp = name.find('/');
	}
	return name;
}