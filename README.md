# core8 [![Build Status](https://travis-ci.org/benvenutti/core8.svg?branch=master)](https://travis-ci.org/benvenutti/core8) [![Build status](https://ci.appveyor.com/api/projects/status/k4ci4ocbxed2xufo/branch/master?svg=true)](https://ci.appveyor.com/project/benvenutti/core8/branch/master) [![Coverage Status](https://coveralls.io/repos/github/benvenutti/core8/badge.svg?branch=master)](https://coveralls.io/github/benvenutti/core8?branch=master)

**core8** is a fully featured [CHIP8](https://en.wikipedia.org/wiki/CHIP-8) interpreter that offers a virtual machine able to run CHIP8 binaries. The **core8**'s VM uses a simple I/O device interface which can be easily connected to a graphical user interface so it can act as an engine for an actual emulator.

## Overview

**core8** is a lib written in C++14 that exposes a small interface to cycle a CHIP8 interpreter and to execute I/O operations (audio, video and keyboard). Once a valid binary is loaded, the VM can run its instructions, generating side effects on its memory frame according to the CHIP8's specifications.

It is important to notice that this project is **not an actual emulator**, but it is an engine to can actually drive an emulator.

## Building core8 from source

You can also build the lib from source. The building process of **core8** is managed by [CMake](https://cmake.org/) scripts. The only dependency that the lib relies on it's the [Catch](https://github.com/philsquared/Catch) unit test framework. Yet, that is also managed by the scripts, so all you need to make sure is that you have CMake and a C++14 compliant compiler.

### Supported compilers

Currently, this project supports linux/osx platforms and it has a continuous integration system over [Travis CI](https://travis-ci.org/benvenutti/core8).
The following compilers are known to work for **core8**:

- GCC 4.9
- GCC 5.4
- GCC 6.2
- Clang 3.6.2
- Clang 3.7.1
- AppleClang xcode 7.3
- AppleClang xcode 8.0

### Compiling

Run the classic **cmake + make** on the source directory. It is recommend to run **cmake** from out of source, that is, usually from a *build* directory inside the source directory.

```shh
core8$ mkdir build && cd build
core8/build$ cmake ..
core8/build$ make
```

### Running tests

To run the available tests, you need to execute the *test* target using **make test**, like this:

```shh
core8/build$ make test
Running tests...
Test project core8/build
    Start 1: Core8Test
1/1 Test #1: Core8Test ........................   Passed    0.03 sec

100% tests passed, 0 tests failed out of 1
```
## Next steps

Here is a list with future plans for the lib:

- Windows support
- bundled debug command line tool
