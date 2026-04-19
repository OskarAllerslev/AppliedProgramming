
#include "2_6.h"
#include <cmath>

/*
we have the function f(x) = e^x + x^3 - 5 
f'(x) = e^x + 3x^2 
*/

// implement both f(x) and f'(x) below?
double f_x(double x)
{
    return std::exp(x) + std::pow(x, 3) - 5;
}

double f_prime_x(double x)
{
    return std::exp(x) + 3 * std::pow(x, 2);
}




double newton_Raphson(double initialGuess, double epsilon)
{
    // we make a while loop here. 
    // while error > epsilon then we proceed 
    double x_prev = initialGuess;
    double x_next = x_prev - f_x(x_prev) / f_prime_x(x_prev);

    while (std::abs(x_next - x_prev) >= epsilon) 
    {
        x_prev = x_next;
        x_next = x_prev - f_x(x_prev) / f_prime_x(x_prev);
        
    }
    return x_next;

}