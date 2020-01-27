cmake_minimum_required(VERSION 3.12)
project(euclid-algo C)

add_executable(euclid-algo
        main.c
        input.txt)

FILE(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})

set_target_properties(euclid-algo PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
        C_FLAGS "-O2"
        RESOURCE "${RESOURCE_FILES}")