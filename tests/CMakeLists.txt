# Add executable for Unit Tests
add_executable(UnitTests UnitTests.cpp)

# Link the core library with the test executable
target_link_libraries(UnitTests PRIVATE FinanceCore GTest::gtest GTest::gtest_main)

# Find GoogleTest
find_package(GTest REQUIRED)

# Include GTest directories for tests
target_include_directories(UnitTests PRIVATE ${GTEST_INCLUDE_DIRS})

# Enable testing
enable_testing()

# Add tests
add_test(NAME UnitTests COMMAND UnitTests)
