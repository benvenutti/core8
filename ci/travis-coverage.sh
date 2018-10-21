#!/bin/bash

if [ "$BUILD_TYPE" == "Coverage" ]; then
  lcov --gcov-tool $(which ${GCOV}) -d . -c -o coverage.info
  lcov --gcov-tool $(which ${GCOV}) -r coverage.info '/usr/*' 'libs/*' 'model/tests/*' -o coverage.info
  lcov --gcov-tool $(which ${GCOV}) -l coverage.info
  bash <(curl -s https://codecov.io/bash) -X gcov || echo "Codecov did not collect coverage reports"
fi
