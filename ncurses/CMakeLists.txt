cmake_minimum_required(VERSION 3.17)
project(Lem_IPC_Ncurses C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror g3 -O0 -ggdb")

add_executable(Lem_IPC_Ncurses
    sources/main.c
)

target_link_libraries(Lem_IPC_Ncurses ncurses pthread rt IPC_lib)
target_include_directories(Lem_IPC_Ncurses PRIVATE includes)