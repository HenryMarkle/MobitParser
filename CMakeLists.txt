cmake_minimum_required(VERSION 3.16.0)
project(MobitParser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB LIB_SOURCES src/*.cpp)
add_library(MobitParser STATIC ${LIB_SOURCES})
target_include_directories(MobitParser PUBLIC include)
