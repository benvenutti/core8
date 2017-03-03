#!/usr/bin/env bash

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  sudo -E apt-get update -qq

  if [ "$COMPILER" == "clang++" ]; then
    sudo apt-get -y install libc++-dev
  elif [ "$COMPILER" == "clang++-3.7" ]; then
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.7 60 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.7
  fi
fi

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  pip install --user cpp-coveralls
fi
