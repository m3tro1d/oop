cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(default_build_type "Release")

# Supply catch2
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE catch2/)

add_subdirectory(lab1)
add_subdirectory(lab2)
