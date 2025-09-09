cmake_minimum_required(VERSION 3.15...4.1)
project(
  shape-movement
  VERSION 1.0
  DESCRIPTION "First lab work on computer vision"
  HOMEPAGE_URL https://github.com/serrhiy/shape-movement
  LANGUAGES CXX
)

option(BUILD_TESTING "Build tests" OFF)
include(CTest)

add_subdirectory(lib)
add_subdirectory(src)

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
