# core8 [![Build Status](https://travis-ci.org/benvenutti/core8.svg?branch=master)](https://travis-ci.org/benvenutti/core8) [![Coverage Status](https://coveralls.io/repos/github/benvenutti/core8/badge.svg?branch=master)](https://coveralls.io/github/benvenutti/core8?branch=master) [![badge](https://img.shields.io/badge/conan.io-core8%2F0.1-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/core8/0.1/benvenutti/testing)

**core8** is a small interpreter that emulates the chip8 platform. This project is a C++ lib that offers a virtual machine able to run chip8 binaries. The **core8**'s VM uses a simple I/O interface which can be easily connected to a graphical user interface so it can act as an engine for a chip8 emulator.

The **core8** lib is written in C++14.

## Overview

![Overview of core architecture](https://github.com/benvenutti/core8/blob/issue-36/images/core8-overview.png)

### Branches

Here is the starting branching model:

**master**: main development branch;

**issue-"x"**: used to implement issue "x" during development. Should branch off master and merge back into master;

**release**: for stable releases.
