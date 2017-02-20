#!/usr/bin/env bash

if [ "$IS_COVERAGE_BUILD" == 0 ]; then
  mkdir build
  cd build
fi

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  flags="-g -O0 --coverage"
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="$flags" -DCMAKE_CXX_COMPILER=$COMPILER .
elif [ "$TRAVIS_OS_NAME" == "linux" ] && [ "$COMPILER" == "clang++" ]; then
  cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_CXX_FLAGS="-stdlib=libc++" ..
elif [ "$TRAVIS_OS_NAME" == "linux" ] && [ "$COMPILER" == "g++-4.9" ]; then
  cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_CXX_FLAGS="-std=c++1y" ..
else
  cmake -DCMAKE_CXX_COMPILER=$COMPILER ..
fi

make
make test CTEST_OUTPUT_ON_FAILURE=TRUE