# HTMLParser

## Description 
Homework4 (2019.4.7)  

Construct DOM tree from given html file and output it by the following tree structure:  

```
[TAG] <tagName>  
attributeName1:attributeValue1   
attributeName2:attributeValue2  
    [TAG] <tagName>  
    [TEXT] Content  
    [COMMENT] Content  
    ...  
```
## Usage

```
$ make
$ ./run [filename]
```  


## Example
example.html
```html
<html>
    <head>
        <title>Who AK IOI</title>
        <meta charset="utf-8">
    </head>
    <body>
    
        <img src="https://html.men.ci/avatar.png" width="25" height=“25”>
        Who AK IOI?
    
        <a>ceerRep</a>
        <ins>KyleYoung</ins>
        <del>Miloris</del>
        <li style="font-family: 'Comic Sans MS'; color: #66ccff;"><b>Menci</b></li>
        <!--li><font face="Comic Sans MS">moorhsum</font></li-->

        <p>
            Music:
            <audio src="https://html.men.ci/fa.mp3" controls>
        </p>
    </body>
</html>
```
result
```
[TAG] <html>
    [TAG] <head>
        [TAG] <title>
            [TEXT] Who AK IOI
        [TAG] <meta>
        charset:utf-8
    [TAG] <body>
        [TAG] <img>
        src:https://html.men.ci/avatar.png
        width:25
        height:“25”
            [TEXT] Who AK IOI?
            [TAG] <a>
                [TEXT] ceerRep
            [TAG] <ins>
                [TEXT] KyleYoung
            [TAG] <del>
                [TEXT] Miloris
            [TAG] <li>
            style:font-family: 'Comic Sans MS'; color: #66ccff;
                [TAG] <b>
                    [TEXT] Menci
            [COMMENT] <!--li><font face="Comic Sans MS">moorhsum</font></li-->
            [TAG] <p>
                [TEXT] Music:
                [TAG] <audio>
                src:https://html.men.ci/fa.mp3
                controls:
```

## API

### `DOM::DOM`
Construct a `DOM` object from a `std::istream` or a `std::string`.

```cpp
//DOM::DOM(std::ifstream &is);
DOM DOMTree1(std::cin);

//DOM::DOM(std::string rawHTML);
DOM DOMTree2("<a>miloris</a>");
```

### `DOM::showTree`
Print the DOM tree of HTML to the terminal.
```cpp
//void DOM::showTree();
DOMTree.showTree();
```

### `DOM::extractTagName`
Find all the named tag and print their subtree to the terminal.
```cpp
//void DOM::extractTagName(std::string tagName);
DOMTree.extractTagName("a");
```

### `DOM::extractTagAttr`
Find all the named attributes in named tag and print them to the terminal.
```cpp
//void DOM::extractTagAttr(std::string tagName, std::string attrName);
DOMTree.extractTagName("a", "href");
```

### `DOM::showAllText`
Find all `TEXT` elements in HTML and print them to terminal.
```cpp
//void DOM::showAllText();
DOMTree.showAllText();
```