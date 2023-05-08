cmake_minimum_required(VERSION 3.16)
project(VisualSVNTask C)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall -O0")
set(CMAKE_C_FLAGS "-Wall -O2")

set(CMAKE_C_STANDARD 11)

add_executable(VisualSVNTask main.c reverser.c reverser.h app.c app.h exception_s.c exception_s.h)
