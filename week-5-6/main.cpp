#include <iostream>
#include <cassert>
#include "Matrix.hpp"

int main() 
{
    std::cout << "--- Tester Matrix og Vector ---" << std::endl;

    Matrix<int> m1(2, 2);
    m1(0,0) = 1; m1(0,1) = 2;
    m1(1,0) = 3; m1(1,1) = 4;

    Matrix<int> m2(2, 2);
    m2(0,0) = 5; m2(0,1) = 6;
    m2(1,0) = 7; m2(1,1) = 8;

    std::cout << "m1(1,0) burde vaere 3, og er: " << m1(1,0) << std::endl;

    Matrix<int> m3 = m1 + m2;
    // Forventet: m1(0,0) + m2(0,0) = 1 + 5 = 6
    std::cout << "m3(0,0) burde vaere 6, og er: " << m3(0,0) << std::endl;

    Matrix<int> m4 = m1 * 10;
    // Forventet: 1 * 10 = 10
    std::cout << "m4(0,0) burde vaere 10, og er: " << m4(0,0) << std::endl;

    Vector<int> v1(2);
    v1[0] = 1; 
    v1[1] = 2;

    Vector<int> v_result = m1 * v1; 
    // Forventet udregning for række 0: (1*1) + (2*2) = 5
    // Forventet udregning for række 1: (3*1) + (4*2) = 11
    std::cout << "v_result[0] burde vaere 5, og er: " << v_result[0] << std::endl;
    std::cout << "v_result[1] burde vaere 11, og er: " << v_result[1] << std::endl;

    Matrix<double> m_double(1, 1);
    m_double(0,0) = 3.14;
    std::cout << "Double test: " << m_double(0,0) << std::endl;


    return 0;
}