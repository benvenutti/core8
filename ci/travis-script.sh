#!/bin/bash

mkdir build
cd build

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_PREFIX_PATH="$(brew --prefix qt)" ..
fi

cat compile_commands.json
cmake --build . -- -j2
ctest -VV .
