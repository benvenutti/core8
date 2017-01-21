#!/usr/bin/env bash

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  coveralls --gcov-options '\-lp'
fi
