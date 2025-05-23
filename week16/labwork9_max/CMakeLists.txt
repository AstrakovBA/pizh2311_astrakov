cmake_minimum_required(VERSION 3.5)

project(
    labwork9
    DESCRIPTION "C++ 2024 labwork9"
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)