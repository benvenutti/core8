#!/usr/bin/env bash

mkdir build
cd build

if [ "$TRAVIS_OS_NAME" == "linux" ] && [ "$COMPILER" == "clang++" ]; then
  cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_CXX_FLAGS="-Wall -stdlib=libc++ -std=c++14" ..
elif [ "$TRAVIS_OS_NAME" == "linux" ] && [ "$COMPILER" == "g++-4.9" ]; then
  cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_CXX_FLAGS="-Wall -std=c++1y" ..
else
  cmake -DCMAKE_CXX_COMPILER=$COMPILER ..
fi

make
make test CTEST_OUTPUT_ON_FAILURE=TRUE