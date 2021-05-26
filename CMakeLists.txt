cmake_minimum_required(VERSION 3.10)
project(Compilation_SemanticAnalyzer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Compilation_SemanticAnalyzer
        helpers.h
        hw3_output.cpp
        hw3_output.h
        main.cpp
        SymbolTable.cpp
        SymbolTable.h)
