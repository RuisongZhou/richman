cmake_minimum_required(VERSION 3.14)
project(richman C)

set(CMAKE_C_STANDARD 11)

add_executable(richman main.c common.h initialize.h initialize.c command_exec.c command_parser.c  map.c playerMove.c judge.c dump.c action.c tools.c building.c)