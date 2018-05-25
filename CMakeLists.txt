cmake_minimum_required(VERSION 3.5.1)
project(database)

if(CMAKE_COMPILER_IS_GNUCXX)
    # Errors and warnings.
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wextra -Wconversion -Wno-unused-parameter -Wtype-limits -pedantic -pedantic-errors")
    # Valgrind and debug
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
    # Optimizing
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

enable_testing(true)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake.modules/")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
include(ParseAndAddCatchTests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src)
