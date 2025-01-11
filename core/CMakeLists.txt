cmake_minimum_required(VERSION 3.12)
project(FinanceMLCore)

# Use LLVM Clang from Homebrew
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenMP Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib -lomp")

# Add the core library
add_library(FinanceCore
    src/Core.cpp
    src/DataPreprocessing.cpp
    src/FeatureEngineering.cpp
    src/MLModels.cpp
)

# Include public headers for FinanceCore
target_include_directories(FinanceCore PUBLIC include)

# Find and configure OpenMP
find_package(OpenMP)

if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found, enabling parallelization.")
else()
    message(WARNING "OpenMP not found, parallelization will not be enabled.")
endif()