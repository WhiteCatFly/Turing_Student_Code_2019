Usage
* You don't need to change any parameter, just 'make' then './crawler + url'
* excmple: ./crawler http://econ.ruc.edu.cn

File Declaration
* CmdOrder: Contain the orders I want cmd to execute
* HTMLParserBase: The base class of class HTMLParser
* HTMLParser: A class which is used to get url, title and body of a webpage
* html: The class contains HTMLParser, it is used to all webpages of a website circularly
* easylogging++: Used to record log.
* urlset.txt: Used to record the urls which have been crawling. 
* When facing interruption, program will read the txt file to continue.
