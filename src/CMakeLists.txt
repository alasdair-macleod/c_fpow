cmake_minimum_required(VERSION 3.12)
project(cfpow)
add_subdirectory(nmath)

set(CMAKE_C_STANDARD 90)

add_library(fpow SHARED fpow.c)