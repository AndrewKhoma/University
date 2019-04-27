cmake_minimum_required(VERSION 3.13)
project(cryptology)

set(CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_LIST_DIR}/cmake
        ${CMAKE_MODULE_PATH})

find_package(GTest REQUIRED)
find_package(GMP REQUIRED)

enable_testing()

add_subdirectory(number-theory)
add_subdirectory(symmetric-block-cipher)
add_subdirectory(hash-function)
add_subdirectory(tests)