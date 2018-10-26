cmake_minimum_required(VERSION 3.10)
project (GameBoyEmulator LANGUAGES CXX)

include(cmake/tools.cmake)

file(GLOB_RECURSE CXX_SRC_FILES 
    src/*.cpp
    src/instruction/*.cpp
    src/memory/*.cpp
)

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;checks=-*,readability-*")

set(CMAKE_CXX_STANDARD 17)

add_executable(gameboy ${CXX_SRC_FILES})
