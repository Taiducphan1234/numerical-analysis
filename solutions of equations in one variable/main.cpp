#include <cmath>
#include <iostream>
#include "equations-solver.h"

using namespace std;

double func_test (double x) {
    return x*x*x + 4*x*x - 10.0;
}

//Actually this function is equivalent to the function above in the sense of finding a positive solution
double fixed_point_solver_test(double x) {
    return 0.5 * sqrt(10 - x*x*x);
}

int main() {
    cout << "Considering the function x^3 - 4x^2 - 10" << endl;
    cout << "The iterations for bisection are as follow" << endl;
    bisection_solver(1, 2, func_test);
    cout << "The iterations for fixed-point method are as follow (notice that actually we are trying to find a solution for the same equation)" << endl;
    fixed_point_solver(1.5, fixed_point_solver_test);
    cout << "The iterations for Newton-Raphson are as follow" << endl;
    newton_raphson_solver(1.5, func_test);
    cout << "The iterations for secant method are as follow" << endl;
    secant_solver(1, 2, func_test);
    cout << "The iterations for false position method are as follow" << endl;
    false_position_solver(1, 2, func_test);
    return 0;
}
