# HTML Parser
The task of Advanced Programming class on 2019/04/04. C++ BigInteger class.

# Requirements
* C++ compiler with C++11 support
* CMake (>= 3.0)

# Sample
This project contain a sample REPL that read expressions with only one operator from commandline, and print the result. Build it with:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../src
make

./big-integer
```

Then type your expressions in the REPL:

```
>>> 1+2
3
>>> 998244353 * 12345678987654321
12324004333376682654299313
>>> 20000528 - 112233445566778899
-112233445546778371
>>> (EOF to exit)
```

# API
Initialize a BigInteger with a string or integer type, then just use it like a `int`.
