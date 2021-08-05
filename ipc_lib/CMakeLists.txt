cmake_minimum_required(VERSION 3.17)
project(IPC_lib C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror g3 -O0 -ggdb")

add_library(IPC_lib SHARED
    sources/ipc_creation.c
    sources/ipc_freeing.c
    sources/utils.c
)

target_include_directories(IPC_lib PUBLIC includes)