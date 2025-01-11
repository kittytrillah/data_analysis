# Add executable for tests
add_executable(UnitTests UnitTests.cpp)

# Link the core library with the test executable
target_link_libraries(UnitTests PRIVATE FinanceCore)

# Find and link GoogleTest
find_package(GTest REQUIRED)
target_link_libraries(UnitTests PRIVATE GTest::gtest GTest::gtest_main)

# Enable testing
include(GoogleTest)
gtest_discover_tests(UnitTests)
