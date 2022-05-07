cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(oop LANGUAGES CXX)

# Set to 17 for SFML toolchain
set(CMAKE_CXX_STANDARD 17)

# catch2
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE libs/catch2/)

# fakeit
add_library(fakeit INTERFACE)
target_include_directories(fakeit INTERFACE libs/fakeit/)


add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)
add_subdirectory(lab5)
add_subdirectory(lab6)
add_subdirectory(lab7)
