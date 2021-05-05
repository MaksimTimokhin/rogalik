cmake_minimum_required(VERSION 3.14)
project(rogalik)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)