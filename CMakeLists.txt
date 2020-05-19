cmake_minimum_required(VERSION 3.9)

# Name the project V6502
project(V6502)

# Find all test files
file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

# Create an executable for testing
add_executable(Tests ${TEST_SRCS})

# Link the include directory
target_include_directories(Tests PUBLIC include)