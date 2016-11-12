#!/usr/bin/env bash

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
  sudo -E apt-get update -qq

  if [ "$COMPILER" == "clang++" ]; then
    sudo apt-get -y install libc++-dev
  fi
fi