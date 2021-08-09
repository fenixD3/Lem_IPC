cmake_minimum_required(VERSION 3.17)
project(Lem_IPC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror g3 -O0 -ggdb")

add_executable(Lem_IPC
    sources/main.c
    sources/check_input.c
    sources/ipc_management.c
    sources/player_management.c
    sources/game.c
    sources/logger/logger.c
    sources/logger/logger_utils.c
    sources/moving.c
    sources/enemy_searching.c
    sources/directions.c sources/graphic.c sources/signals.c)

add_executable(Lem_IPC_Ncurses
    ncurses/sources/main.c
    ncurses/sources/printing.c)

add_subdirectory(ipc_lib)

target_include_directories(Lem_IPC PRIVATE
        includes
        includes/logger)

target_include_directories(Lem_IPC_Ncurses PRIVATE ncurses/includes)

target_link_libraries(Lem_IPC IPC_lib)
target_link_libraries(Lem_IPC_Ncurses ncurses IPC_lib)