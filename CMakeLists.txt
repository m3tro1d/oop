cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(oop LANGUAGES CXX)

# Set to 17 for SFML toolchain
set(CMAKE_CXX_STANDARD 20)

# Supply catch2
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE catch2/)

add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)
