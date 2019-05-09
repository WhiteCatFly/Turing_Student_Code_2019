# BigInteger
The task of Advanced Programming class on 2019/04/04. C++ BigInteger class.

# Requirements
* C++ compiler with C++11 support
* CMake (>= 3.0)

# Sample
This project contains the specfied testcases `main.cc`.

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../src
make

./big-integer
```

The output has been uploaded in [`print.out`](print.out).

# API
Initialize a BigInteger with a string or integer type, then just use it like a `int`.
