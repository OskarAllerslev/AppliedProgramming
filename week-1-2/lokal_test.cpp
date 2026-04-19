
#include <iostream>
// #include "2_6.h"
#include "3_3.h"
#include "5_4.h"


int main() 
{
    // double f_val = f_x(0.0);
    // double f_prime_val = f_prime_x(0.0);
    // std::cout << "f value in 0 " << f_val << std::endl;
    // std::cout << "f prime  value in 0 " << f_prime_val << std::endl;
    // double initial_guess = 2;
    // double epsilon = 0.000001;
    // double NR = newton_Raphson(initial_guess,epsilon);
    // std::cout << "newton raphson i " << initial_guess << " resultere i " << NR << std::endl;


    // int n = 100;
    // implicit_Euler(n);
    // std::cout << "tjek om der er en data fil" << std::endl;

    double test_array[4] = {1.0, 2.0, 9.0, 7.8};
    double std_err = calc_std(test_array, 4);

    std::cout << "the standard error of our array: " << *test_array << "\n" 
    << " is " << std_err << std::endl;


}
