cmake_minimum_required(VERSION 3.10)
project(sandpile_simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл
add_executable(sandpile main.cpp)
