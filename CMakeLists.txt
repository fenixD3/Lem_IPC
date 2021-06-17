cmake_minimum_required(VERSION 3.17)
project(Lem_IPC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(
        includes
        includes/logger)

add_executable(Lem_IPC
        sources/main.c
        sources/check_input.c
        sources/ipc_management.c
        sources/ipc_creation.c
        sources/ipc_freeing.c
        sources/player_management.c
        sources/game.c
        sources/logger/logger.c
        sources/logger/logger_utils.c sources/utils.c)

target_link_libraries(Lem_IPC pthread rt)