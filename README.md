# core8 [![Build Status](https://travis-ci.org/benvenutti/core8.svg?branch=master)](https://travis-ci.org/benvenutti/core8) [![Coverage Status](https://coveralls.io/repos/github/benvenutti/core8/badge.svg?branch=master)](https://coveralls.io/github/benvenutti/core8?branch=master) [![badge](https://img.shields.io/badge/conan.io-core8%2F0.1-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/core8/0.1/benvenutti/testing)

**core8** is a fully featured [CHIP8](https://en.wikipedia.org/wiki/CHIP-8) interpreter in C++ that offers a virtual machine able to run CHIP8 binaries. The **core8**'s VM uses a simple I/O device interface which can be easily connected to a graphical user interface so it can act as an engine for an actual emulator.

## Overview

**core8** is a lib written in C++14 that exposes a small interface to cycle a CHIP8 interpreter and to execute I/O operations (audio, video and keyboard). Once a valid binary is loaded, the VM can run its instructions, generating side effects on its memory frame according to the CHIP8's specifications.

It is important to notice that this project is **not an actual emulator**, but it is an engine to can actually drive an emulator.

## Design

The lib entities were designed as independent components (classes, if you will) to mirror the following conceptual CHIP8 architecture (here a simplified version is showed):

<p align="center">
  <img src="https://github.com/benvenutti/core8/blob/issue-36/images/core8-overview.png" alt="Overview of core8 architecture">
</p>

While the class `Core8::VM` drives the whole underlying CPU, the pure virtual class `Core8::IoDevice` can be implemented on frameworks like [sfml](http://www.sfml-dev.org/), [SDL](https://www.libsdl.org/), etc. to provide a GUI for the user experience.

### Branches

Here is the starting branching model:

**master**: main development branch;

**issue-"x"**: used to implement issue "x" during development. Should branch off master and merge back into master;

**release**: for stable releases.
