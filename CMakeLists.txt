cmake_minimum_required(VERSION 3.13)
project(Timer CXX) ## precise CXX to ignore identification and checks for C Compiler

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES src/main.cpp
			src/Timer.h)

add_executable(main ${SOURCES})

target_link_libraries(main -lpthread)
