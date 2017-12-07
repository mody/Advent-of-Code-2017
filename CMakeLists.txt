cmake_minimum_required(VERSION 3.0)

project(Puzzle)

find_package(sklik-cmake-utils REQUIRED)

sklik_compile_executable(
    NAME puzzle_01_1
    SOURCES
        puzzle_01_1.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_01_2
    SOURCES
        puzzle_01_2.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_02_1
    SOURCES
        puzzle_02_1.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_02_2
    SOURCES
        puzzle_02_2.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_03_1
    SOURCES
        puzzle_03_1.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_03_2
    SOURCES
        puzzle_03_2.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_04_1
    SOURCES
        puzzle_04_1.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_04_2
    SOURCES
        puzzle_04_2.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_05_1
    SOURCES
        puzzle_05_1.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_05_2
    SOURCES
        puzzle_05_2.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_06_1
    SOURCES
        puzzle_06_1.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)

sklik_compile_executable(
    NAME puzzle_06_2
    SOURCES
        puzzle_06_2.cc
    COMPILE_OPTIONS
        -Wall -std=c++14 -g -O2
)
