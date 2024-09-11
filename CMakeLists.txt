cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled "solutions of equations in one variable/main.cpp"
        "solutions of equations in one variable/equations-solver.cpp"
        "solutions of equations in one variable/equations-solver.h"
        "solutions of equations in one variable/accelerated-solvers.cpp"
        "solutions of equations in one variable/accelerated-solvers.h"
)

