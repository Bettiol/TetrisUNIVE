cmake_minimum_required(VERSION 3.16)
project(TetrisUNIVE C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3 -pedantic-errors")

add_executable(TetrisUNIVE main.c tetris_components.h tetris_components.c tetris_print.h tetris_print.c input_control.h input_control.c tetris_operations.c tetris_operations.h NPC_tetris.c NPC_tetris.h main.h)
