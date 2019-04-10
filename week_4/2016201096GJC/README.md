HTMLParser
* HTMLParser(string url): Construct a object from a url  
 
* HTMLParser(std::ifstream &file): Construct a object from a open file  
 
* ~HTMLParser(): Destruct the object and delete the html file we downloaded when constructing
 
* void DownloadFromUrl(): Download the origin link

* string GetTitle(): Extract the webpage's title

* string GetBody(): Extract the webpage's body

* void DeleteLabel(string& body): Delete the html's labels in the body

* string GetSubLinks(): Extract links in the webpage

* string replace(string str, string pattern, string repattern): Replace some special syntax as punctuation, like blank string and quotation mark

* private member url_: the origin link

* private member location: the location which we download the htmlfile in

* private member html: the webpage's source code

CmdOrder
* There is also a file called CmdOrder.cpp, containing only one function which is used to get a linux order's optimization result

