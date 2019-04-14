## Description

A simple HTML Parser to parse a html web.

May not work well on some denormalized html webs.

The HTML Parser can analyze the tree structure of the html web and output it to "tree.txt", in which the attributes and contents of a tag are also indicated. Also, the title of the html web will be written to "title.txt", the contents will be written to "contents.txt", and the hrefs to "hrefs.txt".

Users can use command line arguments to specify the orgin of the html web to be parsed. The argument "-u" is used for a url (the parser will crawl the corresponding web and then parse it), "-f" for a file name (the parser will read the web from the corresponding file), and "-s" for a string that contains the contents of the web.

## Usage

```bash
make
./prog (-u url) (-f file_name) (-s html_contents)
make clean
```

