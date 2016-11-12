#!/usr/bin/env bash

mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=$COMPILER ..
make
make test CTEST_OUTPUT_ON_FAILURE=TRUE