cmake_minimum_required(VERSION 3.13)
project(Timer CXX) ## precise CXX to ignore identification and checks for C Compiler

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run()

if (NOT EXISTS conanbuildinfo.cmake)
  message(FATAL_ERROR "Conan needs to be executed: conan install <path_to_your_conanfile.txt>")
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(TARGETS)

set(SOURCES src/main.cpp
			src/Timer.h)

add_executable(main ${SOURCES})
target_link_libraries(main ${CONAN_LIBS})