cmake_minimum_required(VERSION 3.10)
project (GameBoyEmulator LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(add_sources)

add_definitions(-std=c++17)

add_subdirectory(src)

declare_executable(gameboy)
