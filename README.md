# Material Point Method
Toy implementation of the material point method in C++

# References

https://www.seas.upenn.edu/~cffjiang/research/mpmcourse/mpmcourse.pdf

# Requirements

To run this code you will need

* The Conan package manager
* CMake
* A C++ compiler compatible with C++17
* Doxygen (optional)

# Compiling and running the code

First, let Conan download the required libraries

```bash
cd build
conan install ..
```

Then, configure and run CMake/Make

```make
cmake ..
make -j
```

The binary to run the code will be in `build/bin/MPM`.

If the online documentation is also wanted, it can be built by running
`doxygen` in the root folder.
