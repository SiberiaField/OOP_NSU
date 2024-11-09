cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(build_main)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp Evolution.cpp)