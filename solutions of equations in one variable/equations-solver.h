//
// Created by Hello on 30.08.2024.
//

#ifndef EQUATIONS_SOLVER_H
#define EQUATIONS_SOLVER_H

using namespace std;

//Solve equations using binary search method
double bisection_solver(double leftBound, double rightBound, double (*function)(double), double tolerance = 1e-6, int maxIterations = 1e6);
double fixed_point_solver(double initialPoint, double (*function)(double), double tolerance = 1e-6, int maxIterations = 1e6);
#endif //EQUATIONS_SOLVER_H
