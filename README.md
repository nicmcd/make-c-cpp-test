make-c-cpp-test
==========

An example project for [make-c-cpp](https://github.com/nicmcd/make-c-cpp).

Example
-------

This is an example C++ project that utilizes most of
the features of the automated Makefile system. The example project uses
two 3rd party libraries, zlib and jsoncpp (must be installed on the system), 
contains a unit test for Google's testing framework, and is compliant with 
Google's cpplint.py syntax style checker. The example is comprised of two
subprojects, one shared library, and one binary.

Environment Setup
-----------------

This example application needs libjsoncpp and libz
```bash
sudo apt-get install libjsoncpp-dev zlib1g-dev
```

Build the project
```bash
make
```

Run the gtest suite
```bash
make check
```

Clean up all object files and binaries
```bash
make clean
```


