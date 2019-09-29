cmake_minimum_required(VERSION 3.14)
project(richman C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c common.c map.c command_exec.c command_parser.c playerMove.c initialize.c dump.c judge.c action.c tools.c building.c)
