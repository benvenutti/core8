#!/usr/bin/env bash

if [ "$IS_COVERAGE_BUILD" == 0 ]; then
  mkdir build
  cd build
fi

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  flags="-g -O0 --coverage"
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="$flags" .
elif [ "$TRAVIS_OS_NAME" == "linux" ]; then
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX ..
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  cmake -DCMAKE_C_COMPILER=$COMPILER_CC -DCMAKE_CXX_COMPILER=$COMPILER_CXX -DCMAKE_PREFIX_PATH="`brew --prefix qt`" ..
fi

make
make test CTEST_OUTPUT_ON_FAILURE=TRUE