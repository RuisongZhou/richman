cmake_minimum_required(VERSION 3.14)
project(richman C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c common.h initialize.h  command_exec.c command_parser.c  map.c playerMove.c judge.c dump.c action.c)
