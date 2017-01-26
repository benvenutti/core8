#!/usr/bin/env bash

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  coveralls --exclude externals --gcov-options '\-lp'
fi
