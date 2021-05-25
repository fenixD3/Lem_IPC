cmake_minimum_required(VERSION 3.17)
project(Lem_IPC C)

set(CMAKE_C_STANDARD 99)

include_directories(
        includes
        includes/logger)

add_executable(Lem_IPC
        sources/main.c
        sources/check_input.c
        sources/ipc_management.c
        sources/ipc_creation.c
        sources/ipc_closing.c
        sources/player_management.c
        sources/game.c)

target_link_libraries(Lem_IPC pthread rt)