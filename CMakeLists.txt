cmake_minimum_required(VERSION 3.15...3.30)

project(
    catex
    VERSION 1.0
    LANGUAGES C
)

add_custom_command(move
    COMMAND mv lib* include/
    COMMENT "Moving data"
)

add_dependencies(catex move)

add_library(catex STATIC src/catex.c include/catex.h)
