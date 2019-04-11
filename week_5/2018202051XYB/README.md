# BigInteger

## Description 
Homework5 on 2019.4.4

A 10-based `BigInteger` class.
`main.cpp` is an example.

## Usage

main(example)
```
$ make
$ ./run 
```  

checker(check with random data)
```
$ make check
```


## API

### `BigInteger::BigInteger`
Construct a `BigInteger` object from a `int` or a `std::string`.

```cpp
//BigInteger::BigInteger(int x);
BigInteger a(19260817);

//BigInteger::BigInteger(std::string str);
BigInteger b("-19260817");
```
