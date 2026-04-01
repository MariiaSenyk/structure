cmake_minimum_required(VERSION 4.0)
project(DataStructuresAndAlgorithms)

set(CMAKE_CXX_STANDARD 20)

add_library(DataStructuresAndAlgorithms STATIC library.cpp
        lab2/task1.cpp
        lab2/task2.cpp
        lab2/task3.cpp
        lab2/task4.cpp
        lab3/task1.cpp
        lab3/task2.cpp
        lab3/task3.cpp
        lab4/task.cpp
        lab5/task1.cpp
        lab5/task2.cpp
        lab5/task3.cpp
        lab6/task1.cpp
        lab6/task2.cpp
        lab6/task3.cpp
        lab6/task4.cpp
)
