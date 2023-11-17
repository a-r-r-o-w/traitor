# traitor

> Have you ever wanted/were required to sort an array of integers at compile-time? I'm hoping not...

Experiments with C++ template metaprogramming and compile-time hacking.

### installation

You require a C++ compiler installed with C++20 support and CMake. The programs also build with older C++ versions, but the CMakeLists file is configured to use C++20.

```bash
# Tested on g++-10 and above, and clang++-14.

git clone https://github.com/a-r-r-o-w/traitor.git
cd traitor
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE .. # If you want to build in debug mode, use -DCMAKE_BUILD_TYPE=DEBUG
make -j4
```

### about

I'm using this repository to dump my experiments with C++ template metaprogramming and learn more about compile-time programming. My end goal is to develop a small library for personal use and create all major data structures and algorithms that work at compile-time for fun. Currently, the repository contains the following:

- Bubble sort
- Factorial
- Fibonacci
- For loop - templated and constexpr based; (refer for compile-time if-else)
- GCD
- Insertion sort
- Detecting odd number of template arguments - can be extended to any such condition
- Selection sort
