cmake_minimum_required(VERSION 3.3.2)

project(CppWebService VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(vendor)
add_subdirectory(src)

find_package(GTest)

if (GTEST_FOUND)
    enable_testing()
    add_subdirectory(tests)
else ()
    message(WARN "no tests: did not find GTest")
endif ()