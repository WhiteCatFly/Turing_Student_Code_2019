paser : main.o Html.o Url.o TagNode.o StringModify.o Html.h Url.h TagNode.h StringModify.h
	g++ -std=c++17 -o paser main.o Html.o Url.o StringModify.o TagNode.o -g
main.o : main.cpp TagNode.h Html.h Url.h
	g++ -std=c++17 -c main.cpp -g
TagNode.o : TagNode.cpp TagNode.h Html.h Url.h
	g++ -std=c++17 -c TagNode.cpp -g
Url.o : Url.cpp Url.h StringModify.h
	g++ -std=c++17 -c Url.cpp -g
StringModify.o : StringModify.cpp StringModify.h
	g++ -std=c++17 -c StringModify.cpp -g
Html.o : Html.cpp Html.h StringModify.h Url.h TagNode.h
	g++ -std=c++17 -c Html.cpp -g
clean :
	rm -r -f paser main.o Html.o Url.o StringModify.o TagNode.o