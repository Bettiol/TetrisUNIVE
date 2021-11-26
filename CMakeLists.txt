cmake_minimum_required(VERSION 3.16)
project(TetrisUNIVE C)

set(CMAKE_C_STANDARD 99)

add_executable(TetrisUNIVE main.c tetris_components.h tetris_components.c tetris_print.h tetris_print.c input_control.h input_control.c)
