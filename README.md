# core8 ![Build Status](https://github.com/benvenutti/core8/actions/workflows/ci.yaml/badge.svg) [![Coverage Status](https://coveralls.io/repos/github/benvenutti/core8/badge.svg?branch=master)](https://coveralls.io/github/benvenutti/core8?branch=master) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**core8** is a [CHIP8](https://en.wikipedia.org/wiki/CHIP-8) emulator that offers a Qt GUI to run CHIP8 binaries.

## Building core8

The building process of **core8** is managed by [CMake](https://cmake.org/) scripts. The following list enumerates all dependencies and requirements to build the project:

- C++20 compiler
- CMake 3.25 or higher
- Qt 6.5
- Catch 2 (this dependency is managed by the main CMake script)

### Configure & Compile

It is recommended to configure the build out-of-source, so that the source tree and the build tree are separated. The most usual way to achieve this is to create a **build** directory inside the source directory:

```shh
core8$ mkdir build && cd build
core8/build$ cmake ..
core8/build$ cmake --build .
```

### Running tests

To run the available tests after a successful build, you need to execute the **test** target. One way of doing this is using `ctest` the build folder. Here is an example:

```shh
core8/build$ ctest .
Running tests...
Test project /home/diogo/projects/core8/build
    Start 1: ModelTestSuite
1/1 Test #1: ModelTestSuite ...................   Passed    0.04 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.26 sec
```
