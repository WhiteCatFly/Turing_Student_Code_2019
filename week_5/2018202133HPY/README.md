
# Simple HTML Parser 

This is a simple HTML parser. 

# Usage 

```
$ make
$ # parse <stdin> 
$ ./main  
$ # parse file
$ ./main hack_data/1.html  
$ # parse and highlight selected elements 
$ ./main hack_data/selector_test.html -q 'code.sample' 
```

# Classes
## `cowr::LexerStateBase`
Base class of lexer states.

## `cowr::HTMLElement`
Base class of HTML elements.
### `cowr::HTMLElement::make_unique_from_token`
Create element from token.

## `cowr::HTMLTextElementBase`
Base class of text-like elements, like `cowr::HTMLTextElement`, `cowr::HTMLCommentElement`, `cowr::HTMLUnknownElement`

## `cowr::HTMLTagElement`
Tag element.

## `cowr::HTMLNonEmptyTagElement`
Tag element which have children.

### `cowr::HTMLNonEmptyTagElement::$`
Simple selector used like jQuery, but only implemented some selectors.

#### <code><i>tagname</i></code>
Select tags by its tag name. `*` or omitted for all.

#### <code>.<i>class</i></code>
Select tags by its class.

#### <code>#<i>id</i></code>
Select tags by its id.

#### <code>[<i>attr-expr</i>]</code>
Select tags by its attributes.

##### <code>[<i>attr</i>]</code>
Have attribute named *attr*.

##### <code>[<i>attr</i>=<i>value</i>]</code>
Have attribute named *attr* and its value is *value*.

##### <code>[<i>attr</i>!=<i>value</i>]</code>
The value of *attr* is not *value*.

##### <code>[<i>attr</i>$=<i>value</i>]</code>
The value of *attr* has a suffix of *value*.

## `cowr::HTMLDocument`
The root of DOM tree.
