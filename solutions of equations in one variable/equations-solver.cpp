//
// Created by Hello on 30.08.2024.
//
#include "equations-solver.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
double bisection_solver(double leftBound, double rightBound, double (*f)(double), double tolerance, int maxIterations) {
    double a = leftBound;
    double b = rightBound;
    //FA means f(a), similar for later naming
    double FA = f(a);
    double FB = f(b);

    //If two values of functions at said boundary are not of opposite signs, then halt
    if (FA * FB > 0) {
        throw std::invalid_argument("The algorithm requires functions value at the boundaries to be of opposite signs");
    }

    else {
        for (int i = 1; i <= maxIterations; i++) {
            double p = a + (b - a)/2;
            double FP = f(p);
            std::cout << "Iteration " << i << ':' << a << " " << b << " " << p << " " << FP << endl;
            if (abs(FP) < tolerance) {
                return p;
            }

            // We want to set new boundary in the divide step so that in the next iteration, the values of the function
            // at the two new boundary are still of opposite signs
            if (FA * FP > 0) {
                a = p;
                FA = FP;
            } else b = p;
        }
    }
    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " steps.");
}

double fixed_point_solver(double p0, double (*f)(double), double tolerance, int maxIterations) {
    int i = 1;
    while (i <= maxIterations) {
        double p = f(p0);
        if (abs(p - p0) < tolerance) return p;
        i = i + 1;
        p0 = p;
    }
    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " steps.");
}


