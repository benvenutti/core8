file(GLOB sources *.cpp)

set(TEST_NAME core8-test)

add_executable(${TEST_NAME} ${sources})
target_link_libraries(${TEST_NAME} PRIVATE core8 catch)

add_test(NAME Core8Test COMMAND ${TEST_NAME})
