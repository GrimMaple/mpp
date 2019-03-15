cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

add_subdirectory(third_party/googletest/googletest)

enable_testing()

add_subdirectory(tests)