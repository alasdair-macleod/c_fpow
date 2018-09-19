cmake_minimum_required(VERSION 3.12)
project(cfpow C)
add_subdirectory(nmath)

set(CMAKE_C_STANDARD 99)

add_library(fpow SHARED fpow.c)
target_link_libraries(fpow nmath)

add_executable(main main.c)
target_link_libraries(main fpow)