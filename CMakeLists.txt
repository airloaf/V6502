cmake_minimum_required(VERSION 3.9)

# Library locations (Change these to the appropriate path on your machine)
set(INCLUDE_DIR C:/DevelopmentLibraries/include/)
set(LIB_DIR C:/DevelopmentLibraries/lib/x64)

# The type of library, STATIC or SHARED
set(LIB_TYPE STATIC)

# Name the project V6502
project(V6502_Project)

# Find all source files
file(GLOB_RECURSE LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/V6502/*.cpp)

# Create a static library
add_library(V6502 ${LIB_TYPE} ${LIB_SRCS})

# Include the library headers
target_include_directories(V6502 PUBLIC include)

set(BOOST_INCLUDEDIR ${INCLUDE_DIR})
# Find the boost headers so we can use the unit test library
find_package(Boost 1.66.0)
# If we found boost, build the test executable
if(Boost_FOUND)
    # Find all test files
    file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)
    # Create an executable for testing
    add_executable(Tests ${TEST_SRCS})
    
    # Link the 6502 library to the tests
    target_link_libraries(Tests V6502)
    # Link the include directory and Boost headers
    target_include_directories(Tests PUBLIC include)
    target_include_directories(Tests PUBLIC ${Boost_INCLUDE_DIRS})
endif()

# Check if we have ncurses installed
find_package(Curses)
if(CURSES_FOUND)
    # Find all test files
    file(GLOB_RECURSE MONITOR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/Monitor/*.cpp)
    # Create an executable for monitoring the CPU
    add_executable(CPUMonitor ${MONITOR_SRCS})
    
    # Link the 6502 library to the monitor executable
    target_link_libraries(CPUMonitor V6502)
    # Link the ncurses library to the monitor executable
    target_link_libraries(CPUMonitor ${CURSES_LIBRARIES})
    # Link the include directory and Boost headers
    target_include_directories(CPUMonitor PUBLIC include)
    target_include_directories(CPUMonitor PUBLIC ${CURSES_INCLUDE_DIR})
endif()

# Look for package, Doxygen
# find_package(Doxygen REQUIRED dot)
# # If we have doxygen installed, generate documentation
# if(DOXYGEN_FOUND)
#     # Set the input and cmake doxygen files
#     set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
#     set(DOXYFILE_CMAKE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile_cmake)

#     # Make a copy of the input doxygen file. CMake will generate a custom doxyfile
#     configure_file(${DOXYFILE_IN} ${DOXYFILE_CMAKE} @ONLY)

#     # Command to generate the documentation
#     add_custom_target(documentation 
#         ${DOXYGEN_EXECUTABLE} ${DOXYFILE_CMAKE}
#         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
# endif()