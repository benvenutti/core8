# core8 [![Build Status](https://travis-ci.org/benvenutti/core8.svg?branch=master)](https://travis-ci.org/benvenutti/core8) [![Coverage Status](https://coveralls.io/repos/github/benvenutti/core8/badge.svg?branch=master)](https://coveralls.io/github/benvenutti/core8?branch=master)

**core8** is a fully featured [CHIP8](https://en.wikipedia.org/wiki/CHIP-8) interpreter that offers a virtual machine able to run CHIP8 binaries. The **core8**'s VM uses a simple I/O device interface which can be easily connected to a graphical user interface so it can act as an engine for an actual emulator.

## Overview

**core8** is a lib written in C++14 that exposes a small interface to cycle a CHIP8 interpreter and to execute I/O operations (audio, video and keyboard). Once a valid binary is loaded, the VM can run its instructions, generating side effects on its memory frame according to the CHIP8's specifications.

It is important to notice that this project is **not an actual emulator**, but it is an engine to can actually drive an emulator.

## Design

It is quite common for CHIP8 interpreters/emulators to be implemented in a more procedural approach, usually embedding the GUI framework in the core of the code. This usually leads to high coupling and low cohesion, yet, it usually has a good performance. The **core8** lib proposes a fully testable object-oriented solution, where the entities of the interpreter are highly cohesive classes. *Is there an extra cost in all this?* Yes, the interpreter is not as fast as the monolithic procedural approach. But don't worry, it runs fast enough! :wink:

The lib entities were designed as independent components (classes, if you will) to mirror the following conceptual CHIP8 architecture (here a simplified version is shown):

<p align="center">
  <br>
  <img src="https://github.com/benvenutti/core8/blob/issue-36/images/core8-overview.png" alt="Overview of core8 architecture">
  <br><br>
</p>

While the class `Core8::VM` drives the whole underlying CPU, the pure virtual class `Core8::IoDevice` can be implemented on frameworks like [sfml](http://www.sfml-dev.org/), [SDL](https://www.libsdl.org/), etc. to provide a GUI for the user experience.

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
