project(CJSON)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_CXX_FLAGS "-g")

add_executable(Test Test.c src/Parser.c)
add_library(CJSON OBJECT src/Parser.c)
