cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
link_directories(/usr/include/)
link_libraries(/usr/include/ncurses.h)

project(snake)
add_executable(snake main.c)
