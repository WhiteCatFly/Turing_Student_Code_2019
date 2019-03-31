This is my homework of week_3.
An advanced version of week_2's.

major changes:

Class is added:
	The URL is encapsulated in a class named URL.
	This is a simple application of class, which contains only one std::string.
	Direct modifying of this string is denied, but you still can visit it.
	Some simple operations of this special string are also encapsulated (in class_URL.cpp).
	Function Download, which only has connection with the URL, is encapsulated.

Regex changed:
	(I hate those F*****G strange URLs. )
	Some strange URL formats follow the "href=".
	Match only "\"\"" won't work. And you need to match "''" and "(nothing)>".

Path dealing developed:
	"../" , "./" and "/" is dealed.
	In case the appearance of "//" except "http(s)://".

Personal settings added:
	You are allowed to set the ROOT_URL and BANNER string in parsesettings.log.
	The saving path is not added.

That's all.

You can test my program by:
	make
	./IW

Result:
(ATTENTION: this result was worse than expected. I tested this program in a very bad network environment so many pages were not donwloaded successfully.)
ROOT_URL: http://econ.ruc.edu.cn
Time : 39 minutes		number of pages: 5700+

Next homework I plan to rewrite the Internet Crawler totally.
More and more times of changing make the program a lot of chaos.
HTML structure will be showed as a tree.
More class feature will be reflected.

See you next time.
