cmake_minimum_required(VERSION 2.8)

project(CPP-LRU_CACHE)

enable_testing()

include_directories(
    ${PROJECT_SOURCE_DIR}/include)

add_executable(
    cpp-lru-cache-test
    src/test)

set_target_properties(cpp-lru-cache-test PROPERTIES
    PREFIX ""
    SUFFIX ""
    COMPILE_FLAGS "-std=c++0x -W -Wall -pedantic")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_test(
    NAME cpp-lru-cache-test
    COMMAND cpp-lru-cache-test
)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS cpp-lru-cache-test)
