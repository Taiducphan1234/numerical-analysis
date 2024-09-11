//
// Created by Hello on 11.09.2024.
//

#include "accelerated-solvers.h"

#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <cmath>  // For std::abs

/**
 * Steffensen's method for solving fixed-point problems.
 *
 * This function implements Steffensen's method to accelerate the convergence
 * of a fixed-point iteration using Aitken's Δ² process. The method approximates
 * the solution to the equation f(p_hat) = 0.
 *
 * @param initialPoint The starting point for the iteration.
 * @param function A function pointer representing the function to be solved.
 * @param tolerance The stopping criterion: when the absolute difference between
 *        consecutive estimates is less than this value, the iteration stops.
 * @param maxIterations The maximum number of iterations to perform.
 * @return The approximate solution (fixed point) to the equation f(p_hat) = 0.
 * @throws std::runtime_error if the method does not converge within the specified
 *         number of iterations.
 */
double steffensen_solver(double initialPoint, double (*function)(double), double tolerance, int maxIterations) {
    int i = 1;  // Iteration counter

    // Set up console output formatting for iteration results
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::setw(10) << "Iteration" << std::setw(15) << "p_hat"
              << std::setw(15) << "f(p_hat)" << std::endl;

    double p0 = initialPoint;  // Initial guess for the solution

    while (i <= maxIterations) {
        // Compute successive function values to apply Aitken's Δ² process
        double p1 = function(p0);  // First function evaluation
        double p2 = function(p1);  // Second function evaluation

        // Compute the accelerated estimate using Aitken's Δ² method
        double denominator = p2 - 2 * p1 + p0;
        if (std::abs(denominator) < 1e-12) {  // Prevent division by zero
            throw std::runtime_error("Denominator near zero, method fails at iteration " + std::to_string(i));
        }
        double p = p0 - (p1 - p0) * (p1 - p0) / denominator;

        // Output current iteration result
        std::cout << std::setw(10) << i
                  << std::setw(15) << p
                  << std::setw(15) << function(p) << std::endl;

        // Check if the result is within the specified tolerance
        if (std::abs(p - p0) < tolerance) {
            return p;  // Convergence achieved
        }

        // Update the previous estimate for the next iteration
        p0 = p;
        i++;  // Increment iteration counter
    }

    // If the loop exits without converging, throw an exception
    throw std::runtime_error("No solution found after " + std::to_string(maxIterations) + " iterations.");
}
