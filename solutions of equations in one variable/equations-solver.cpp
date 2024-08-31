//
// Created by Hello on 30.08.2024.
//
#include "equations-solver.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

/**
 * @brief Finds the root of a function using the bisection method.
 *
 * This function implements the bisection method to find the root of a continuous function `f`
 * within a specified interval [leftBound, rightBound]. It assumes that `f(leftBound)` and `f(rightBound)`
 * have opposite signs, indicating that a root lies between them.
 *
 * @param leftBound The left boundary of the interval.
 * @param rightBound The right boundary of the interval.
 * @param f A pointer to the function for which the root is being sought.
 * @param tolerance The acceptable difference between the function value at the root and zero.
 *        The method stops if `|f(p)| < tolerance`.
 * @param maxIterations The maximum number of iterations allowed.
 * @return double The approximate root of the function `f` within the given interval.
 * @throws std::invalid_argument If `f(leftBound)` and `f(rightBound)` do not have opposite signs.
 * @throws std::runtime_error If the method fails to find a root within the given number of iterations.
 */
double bisection_solver(double leftBound, double rightBound, double (*f)(double), double tolerance, int maxIterations) {
    double a = leftBound;
    double b = rightBound;
    double FA = f(a);
    double FB = f(b);

    if (FA * FB > 0) {
        throw std::invalid_argument("The algorithm requires the function values at the boundaries to be of opposite signs.");
    } else {
        std::cout << std::fixed << std::setprecision(6); // Set fixed precision for floating-point numbers

        std::cout << std::setw(10) << "Iteration" << std::setw(15) << "a"
                  << std::setw(15) << "b" << std::setw(15) << "p"
                  << std::setw(15) << "f(p)" << std::endl;

        for (int i = 1; i <= maxIterations; i++) {
            double p = a + (b - a) / 2;
            double FP = f(p);

            std::cout << std::setw(10) << i
                      << std::setw(15) << a
                      << std::setw(15) << b
                      << std::setw(15) << p
                      << std::setw(15) << FP << std::endl;

            if (std::abs(FP) < tolerance) {
                cout << "Algorithm stops with solution: " << p << endl;
                return p;
            }

            if (FA * FP > 0) {
                a = p;
                FA = FP;
            } else {
                b = p;
            }
        }
    }
    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " iterations.");
}

/**
 * @brief Finds a fixed point of a function using the fixed-point iteration method.
 *
 * This function implements the fixed-point iteration method to solve the equation `x = f(x)`.
 * Starting from an initial guess `p0`, the function iteratively computes `p = f(p0)` until
 * the difference between successive iterations is less than the specified `tolerance`.
 *
 * @param p0 The initial guess for the fixed point.
 * @param f A pointer to the function used to compute the fixed point.
 * @param tolerance The convergence criterion. The iteration stops when `|p - p0| < tolerance`.
 * @param maxIterations The maximum number of iterations allowed.
 * @return double The computed fixed point if the method converges within the given number of iterations.
 * @throws std::runtime_error If the method fails to converge to a solution within the specified number of iterations.
 */
double fixed_point_solver(double p0, double (*f)(double), double tolerance, int maxIterations) {
    int i = 1;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::setw(10) << "Iteration" << std::setw(15)  << "p"
          << std::setw(15) << "f(p)" << std::endl;
    while (i <= maxIterations) {
        double p = f(p0);
        if (abs(p - p0) < tolerance) {
            cout << "Algorithm stops with solution: " << p << endl;
            return p;
        }
        std::cout << std::setw(10) << i
                      << std::setw(15) << p0
                      << std::setw(15) << p << std::endl;
        i = i + 1;
        p0 = p;
    }
    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " steps.");
}

/**
 * @brief Calculates the numerical derivative of a function at a given point using the central difference method.
 *
 * This function calculates the numerical derivative of a function `f` at a point `x` using the central difference method.
 * It approximates the derivative by evaluating the function at points slightly offset from `x` by a small step size `h`.
 *
 * @param f A pointer to the function whose derivative is being computed.
 * @param x The point at which the derivative is calculated.
 * @param h The step size used in the central difference formula (default is `1e-10`).
 * @return double The approximate derivative of `f` at `x`.
 */
double numerical_derivative(double (*f)(double), double x, double h=1e-10) {
    //Using central difference
    return (f(x + h) - f(x - h)) / (2 * h);
}

/**
 * @brief Finds the root of a function using the Newton-Raphson method.
 *
 * This function implements the Newton-Raphson method, an iterative root-finding algorithm.
 * Starting from an initial guess, it refines the estimate of the root by using the function's derivative.
 * This method is faster than the bisection method but requires the function's derivative.
 *
 * @param p0 The initial estimate for the root.
 * @param f A pointer to the function whose root is being sought.
 * @param tolerance The convergence criterion. The algorithm stops when |p - p0| < tolerance
 * @param maxIterations The maximum number of iterations allowed.
 * @return double The approximate root of the function if it converges within the given number of iterations.
 * @throws std::runtime_error If the method fails to converge to a solution within the specified number of iterations.
 */
double newton_raphson_solver(double p0, double (*f)(double), double tolerance, int maxIterations) {
    int i = 1;

    std::cout << std::fixed << std::setprecision(6); // Set fixed precision for floating-point numbers

    std::cout << std::setw(10) << "Iteration" << std::setw(15) << "p0"
              << std::setw(15) << "f(p0)" << std::setw(15) << "f'p(0)"
              << std::setw(20) << "p0 - f(p0)/f'(p0)" << std::endl;
    while (i <= maxIterations) {
        double fp = f(p0);
        double fPrimeP0 = numerical_derivative(f, p0);

        if (fPrimeP0 == 0) {
            throw std::invalid_argument("Derivative is zero at the current guess; the algorithm cannot proceed.");
        }

        double p = p0 - fp / fPrimeP0;

        std::cout << std::setw(10) << i
                  << std::setw(15) << p0
                  << std::setw(15) << fp
                  << std::setw(15) << fPrimeP0
                  << std::setw(20) << p << std::endl;

        if (std::abs(p - p0) < tolerance) {
            cout << "Algorithm stops with solution: " << p << endl;
            return p;
        }

        p0 = p;
        i++;
    }
    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " steps.");
}

/**
 * @brief Finds the root of a function using the Secant method.
 *
 * This function implements the Secant method, an iterative root-finding algorithm.
 * Unlike the Newton-Raphson method, the Secant method does not require the calculation of derivatives.
 * Instead, it approximates the derivative using the difference between function values at two points.
 *
 * The algorithm begins with two initial approximations `p0` and `p1` and iteratively improves these
 * estimates until the difference between consecutive approximations is less than the specified `tolerance`,
 * or until the maximum number of iterations is reached.
 *
 * @param p0 The first initial estimate for the root.
 * @param p1 The second initial estimate for the root.
 * @param f A pointer to the function whose root is being sought.
 * @param tolerance The convergence criterion. The algorithm stops when |p_n - p_(n-1)| < tolerance.
 * @param maxIterations The maximum number of iterations allowed.
 * @return double The approximate root of the function if it converges within the given number of iterations.
 * @throws std::runtime_error If the method fails to converge to a solution within the specified number of iterations.
 */
double secant_solver(double p0, double p1, double (*f)(double), double tolerance, int maxIterations) {
    int i = 2;

    double q0 = f(p0);
    double q1 = f(p1);
    std::cout << std::fixed << std::setprecision(6);

    std::cout << std::setw(10) << "Iteration" << std::setw(15) << "p_(n-2)"
          << std::setw(15) << "p_(n-1)" << std::setw(15) << "f(p_(n-2))"
          << std::setw(15) << "f(p_(n-1))" << std::setw(15) << "p_n" << std::endl;
    while (i <= maxIterations) {
        double p = p1 - q1 * (p1 - p0)/(q1 - q0);

        if (abs(p - p0) < tolerance) {
            cout << "Algorithm stops with solution: " << p << endl;
            return p;
        }

        std::cout << std::setw(10) << i
                  << std::setw(15) << p0
                  << std::setw(15) << p1
                  << std::setw(15) << q0
                  << std::setw(15) << q1
                  << std::setw(15) << p << std::endl;

        i = i + 1;

        p0 = p1;
        q0 = q1;
        p1 = p;
        q1 = f(p);
    }

    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " steps.");
}

/**
 * @brief Finds the root of a function using the False Position method.
 *
 * This function implements the False Position method (also known as the Regula Falsi method),
 * an iterative root-finding algorithm. The method combines features of the bisection method
 * and the secant method to find a root of a function. It starts with two initial points,
 * `p0` and `p1`, such that the function values at these points have opposite signs,
 * indicating that a root lies between them.
 *
 * The method iteratively refines these estimates by computing a new point `p` that lies on
 * the line connecting `(p0, f(p0))` and `(p1, f(p1))` and updates the bounds based on the sign
 * of the function at the new point.
 *
 * @param p0 The first initial estimate for the root.
 * @param p1 The second initial estimate for the root.
 * @param f A pointer to the function whose root is being sought.
 * @param tolerance The convergence criterion. The algorithm stops when |p_n - p_(n-1)| < tolerance.
 * @param maxIterations The maximum number of iterations allowed.
 * @return double The approximate root of the function if it converges within the given number of iterations.
 * @throws std::invalid_argument If the initial function values at `p0` and `p1` do not have opposite signs.
 * @throws std::runtime_error If the method fails to converge to a solution within the specified number of iterations.
 */
double false_position_solver(double p0, double p1, double (*f)(double), double tolerance, int maxIterations) {
    int i = 2;

    double q0 = f(p0);
    double q1 = f(p1);

    if (q0 * q1 > 0) {
        throw std::invalid_argument("The algorithm requires the function values at the initial points to have opposite signs.");
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::setw(10) << "Iteration" << std::setw(15) << "p_(n-2)"
              << std::setw(15) << "p_(n-1)" << std::setw(15) << "f(p_(n-2))"
              << std::setw(15) << "f(p_(n-1))" << std::setw(15) << "p_n" << std::endl;

    while (i <= maxIterations) {
        double p = p1 - q1 * (p1 - p0) / (q1 - q0);

        std::cout << std::setw(10) << i
                  << std::setw(15) << p0
                  << std::setw(15) << p1
                  << std::setw(15) << q0
                  << std::setw(15) << q1
                  << std::setw(15) << p << std::endl;

        if (std::abs(p - p1) < tolerance) {
            std::cout << "Algorithm stops with solution: " << p << std::endl;
            return p;
        }

        double q = f(p);

        if (q * q1 < 0) {
            p0 = p1;
            q0 = q1;
        }

        p1 = p;
        q1 = q;
        i = i + 1;
    }

    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " steps.");
}


