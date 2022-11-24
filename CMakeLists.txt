cmake_minimum_required(VERSION 3.16)

include(cmake/gcc-toolchain.cmake)

project(main)


FILE(GLOB FAKE_SRC src/*.c)

add_library(fakeAccess OBJECT ${FAKE_SRC})
target_include_directories(fakeAccess PUBLIC inc)

# test framework
add_subdirectory(test_framework)

# generate the leetcode executable file
add_subdirectory(test)


