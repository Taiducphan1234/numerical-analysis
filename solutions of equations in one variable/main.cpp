#include <iostream>
#include "equations-solver.h"

using namespace std;

double func1 (double x) {
    return x*x*x + 4*x*x - 10.0;
}

int main() {
    bisection_solver(1, 2, func1, 1e-4);
    return 0;
}
