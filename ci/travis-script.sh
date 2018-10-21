#!/bin/bash

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cat compile_commands.json
cmake --build . -- -j2
ctest -VV .
