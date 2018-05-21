#!/usr/bin/env bash

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  sudo -E apt-get update -qq
  sudo -E apt-get install -y qt5-default libboost-all-dev
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then
  brew update
  brew install qt
fi

if [ "$IS_COVERAGE_BUILD" == 1 ]; then
  pip install --user cpp-coveralls
fi
