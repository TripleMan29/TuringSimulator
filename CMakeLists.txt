cmake_minimum_required(VERSION 3.9)
project(TuringSimulator C)

set(CMAKE_C_STANDARD 11)

add_executable(TuringSimulator main.c inputFile.c inputTape.c Source.h Step.c OutputFile.c ConsolePrint.c)