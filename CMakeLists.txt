cmake_minimum_required(VERSION 3.10)
project (GameBoyEmulator LANGUAGES CXX)

set(SRC_ROOT src)
set(BINARY_SRC_ROOT binary_src)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/tools.cmake)
include(cmake/gtest.cmake)

include_directories(${SRC_ROOT})
file(GLOB_RECURSE CXX_LIB_SRC_FILES
    src/*.cpp
    src/instruction/*.cpp
    src/memory/*.cpp
    src/util/*.cpp
)

file(GLOB_RECURSE CXX_TEST_FILES
    test/*.cpp
)

file(GLOB_RECURSE CXX_BINARY_SRC_FILES
    binary_src/main.cpp
)

set(CMAKE_CXX_STANDARD 17)

add_library(gameboy ${CXX_LIB_SRC_FILES})
add_executable(gameboy_binary ${CXX_BINARY_SRC_FILES})
add_executable(gameboy_test ${CXX_TEST_FILES})

target_link_libraries(gameboy_binary gameboy)
target_link_libraries(gameboy_test gameboy gtest_main)

include(GoogleTest)
gtest_discover_tests(gameboy_test)
