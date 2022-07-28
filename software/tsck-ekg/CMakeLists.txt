cmake_minimum_required(VERSION 3.2)
project(Signal.h)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wpedantic")

include_directories(${CMAKE_SOURCE_DIR})

set(TEST_SOURCES
  tests.cpp
  FakeArduino.cpp
  LowPassFilter.test.cpp
  RollingMaximum.test.cpp
  )

add_executable(test ${TEST_SOURCES})
