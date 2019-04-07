# web-crawler
The task of Advanced Programming class on 2019/03/21. C++ web crawler with wget.

# Requirements
* Linux (>= 2.6.27)
* GCC (>= 8), Clang (>= 6)
* CMake (>= 3.0)
* Wget (>= 1.19)

# Build
Replace `clang++-8` with your compiler.

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++-8 ../src
make
```

# Usage
Build and run `./crawler -?` for usage.
