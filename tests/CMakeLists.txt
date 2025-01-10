# Add executable for tests
add_executable(UnitTests UnitTests.cpp)

# Link the core library with the test executable
target_link_libraries(UnitTests PRIVATE FinanceCore)