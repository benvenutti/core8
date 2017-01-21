#!/usr/bin/env bash

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  coveralls --exclude externals --exclude test --exclude CMakeFiles --gcov-options '\-lp'
fi
