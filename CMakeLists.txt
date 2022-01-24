cmake_minimum_required(VERSION 3.16)
project(TetrisUNIVE C)

set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-ansi -pedantic -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(TetrisUNIVE main.c tetris_components.h tetris_components.c tetris_print.h tetris_print.c input_control.h input_control.c tetris_operations.c tetris_operations.h NPC_tetris.c NPC_tetris.h)
