cmake_minimum_required(VERSION 3.9)

# Name the project V6502
project(V6502_Project)

# Find all source files
file(GLOB_RECURSE LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

# Create a static library
add_library(V6502 STATIC ${LIB_SRCS})

target_include_directories(V6502 PUBLIC include)

# Find all test files
file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

# Create an executable for testing
add_executable(Tests ${TEST_SRCS})

# Link the 6502 library to the tests
target_link_libraries(Tests V6502)
# Link the include directory
target_include_directories(Tests PUBLIC include)