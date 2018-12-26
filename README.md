# core8 [![Build Status](https://travis-ci.org/benvenutti/core8.svg?branch=master)](https://travis-ci.org/benvenutti/core8) [![Build status](https://ci.appveyor.com/api/projects/status/k4ci4ocbxed2xufo/branch/master?svg=true)](https://ci.appveyor.com/project/benvenutti/core8/branch/master) [![Coverage Status](https://coveralls.io/repos/github/benvenutti/core8/badge.svg?branch=master)](https://coveralls.io/github/benvenutti/core8?branch=master) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**core8** is a fully featured [CHIP8](https://en.wikipedia.org/wiki/CHIP-8) interpreter that offers a virtual machine able to run CHIP8 binaries. The **core8**'s VM uses a simple I/O device interface which can be easily connected to a graphical user interface so it can act as an engine for an actual emulator.

## Overview

**core8** is a lib written in C++14 that exposes a small interface to cycle a CHIP8 interpreter and to execute I/O operations (audio, video and keyboard). Once a valid binary is loaded, the VM can run its instructions, generating side effects on its memory frame according to the CHIP8's specifications.

It is important to notice that this project is **not an actual emulator**, but it is an engine to can actually drive an emulator.

## Cloning

Make sure to clone the repository with its submodules. One way to do this is as follows:

```shh
git clone --recurse-submodules https://github.com/benvenutti/core8.git
```

## Building core8

The building process of **core8** is managed by [CMake](https://cmake.org/) scripts. The following list enumerates all dependencies and requirements to build the project:

- C++14 compiler
- CMake 3.8
- Qt 5.10
- Libboost 1.54
- Catch 2

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
