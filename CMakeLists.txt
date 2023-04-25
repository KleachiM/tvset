cmake_minimum_required(VERSION 3.24)
project(tvset)

set(CMAKE_CXX_STANDARD 17)

add_executable(tvset main.cpp CTVSet.cpp CTVSet.h InputHandler.cpp InputHandler.h)
add_subdirectory(tests)