cmake_minimum_required(VERSION 3.5.0)
project(MobitParser VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB LIB_SOURCES src/*.cpp)
include_directories(include)
add_library(MobitParser ${LIB_SOURCES})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
