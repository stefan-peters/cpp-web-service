cmake_minimum_required(VERSION 3.3.2)

project(CppWebService VERSION 0.0.1)

set(CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor)
add_subdirectory(src)