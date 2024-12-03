cmake_minimum_required(VERSION 3.5.0)
project(MobitParser VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

file(GLOB LIB_SOURCES src/*.cpp)
include_directories(include)
add_library(MobitParser ${LIB_SOURCES})
target_include_directories(MobitParser PUBLIC include)

include(CTest)
enable_testing()

add_executable(token_test tests/token_test.cpp)
target_link_libraries(token_test PRIVATE MobitParser)
add_test(NAME TokenTest COMMAND token_test)

add_executable(parse_test tests/parse_test.cpp)
target_link_libraries(parse_test PRIVATE MobitParser)
add_test(NAME ParseTest COMMAND parse_test)

add_executable(gcall_test tests/gcall_test.cpp)
target_link_libraries(gcall_test PRIVATE MobitParser)
add_test(NAME GCallParseTest COMMAND gcall_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
