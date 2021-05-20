cmake_minimum_required(VERSION 3.17)
project(Lem_IPC C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

add_executable(Lem_IPC
        sources/main.c
        sources/check_input.c
)