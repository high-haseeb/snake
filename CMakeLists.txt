cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${MATH_INCLUDE_DIR})

project(snake)
add_executable(snake main.c)
target_link_libraries(snake ${CURSES_LIBRARIES})
target_link_libraries(snake ${CURSES_LIBRARIES})
target_link_libraries(snake ${MATH_LIBRARY})
