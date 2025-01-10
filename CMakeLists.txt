cmake_minimum_required(VERSION 3.20)

# Project Name
project(DataAnalysis LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Subdirectories
add_subdirectory(core)
add_subdirectory(tests)