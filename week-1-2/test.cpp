#include <iostream>
#include <cmath>
#include <cassert>

#include "2_6.h"
#include "3_3.h"
#include "5_3.h"
#include "5_4.h"
#include "5_6.h"
#include "5_9.h"
#include "5_10.h" 

// --- HJÆLPEFUNKTIONER ---
bool check_approx(double dit_svar, double facit, double tolerance = 1e-5) {
    return std::abs(dit_svar - facit) < tolerance;
}

void print_result(std::string opgave, bool passed) {
    if (passed) std::cout << "[BESTAAET] " << opgave << "\n";
    else        std::cout << "[FEJLEDE]  " << opgave << "\n";
}

// --- TEST AF DE ENKELTE OPGAVER ---

void test_2_6() {
    std::cout << "Tester 2.6 (Newton-Raphson)...... ";
    double initial_guess = 2.0;
    double epsilon = 0.000001;
    double NR = newton_Raphson(initial_guess, epsilon);
    
    // TJEK: Her skal du skrive det facit, funktionen BURDE give!
    // F.eks. hvis facit er 0.0:
    // bool passed = check_approx(NR, 0.0); 
    // print_result("2.6", passed);
    
    std::cout << "(Kørt uden crash, resultat: " << NR << ")\n";
}

void test_3_3() {
    std::cout << "Tester 3.3 (Implicit Euler)...... ";
    int n = 100;
    implicit_Euler(n);
    std::cout << "(Kørt uden crash, tjek output-filen!)\n";
}

void test_5_4() {
    std::cout << "Tester 5.4 (Standard Deviation).. ";
    double test_array[4] = {1.0, 2.0, 9.0, 7.8};
    double std_err = calc_std(test_array, 4);
    std::cout << "(Kørt uden crash, resultat: " << std_err << ")\n";
}

void test_5_6() {
    std::cout << "Tester 5.6 (Matrix Multiply).... ";
    double A_data[2][2] = {{1, 2}, {3, 4}};
    double B_data[2][2] = {{1, 2}, {3, 4}};
    double res_data[2][2];

    double *A[2] = {A_data[0], A_data[1]};
    double *B[2] = {B_data[0], B_data[1]};
    double *res[2] = {res_data[0], res_data[1]};

    Multiply(res, A, B, 2, 2, 2, 2);

    // Facit for denne matrix-multiplikation er {{7, 10}, {15, 22}}
    bool passed = true;
    if (!check_approx(res[0][0], 7.0)) passed = false;
    if (!check_approx(res[0][1], 10.0)) passed = false;
    if (!check_approx(res[1][0], 15.0)) passed = false;
    if (!check_approx(res[1][1], 22.0)) passed = false;

    print_result("5.6", passed);
}

void test_5_9() {
    std::cout << "Tester 5.9 (solve3by3).......... ";
    double **A = new double*[3];
    for (int i = 0; i < 3; i++) A[i] = new double[3];
    double *b = new double[3];
    double *u = new double[3];

    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 2; A[1][1] = -1; A[1][2] = 1;
    A[2][0] = 3; A[2][1] = 0; A[2][2] = -1;
    b[0] = 9; b[1] = 8; b[2] = 3;

    solve3by3(A, b, u);

    bool passed = true;
    if (!check_approx(u[0], 2.0)) passed = false;
    if (!check_approx(u[1], -1.0)) passed = false;
    if (!check_approx(u[2], 3.0)) passed = false;

    print_result("5.9", passed);

    for (int i = 0; i < 3; i++) delete[] A[i];
    delete[] A; delete[] b; delete[] u;
}

void test_5_10() {
    std::cout << "Tester 5.10 (Gauss Elimination). ";
    int n = 3; // Vi bruger det samme 3x3 system som test!
    double **A = new double*[n];
    for (int i = 0; i < n; i++) A[i] = new double[n];
    double *b = new double[n];
    double *u = new double[n];

    A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
    A[1][0] = 2; A[1][1] = -1; A[1][2] = 1;
    A[2][0] = 3; A[2][1] = 0; A[2][2] = -1;
    b[0] = 9; b[1] = 8; b[2] = 3;

    // Kald din n x n solver (funktionen du lige har skrevet!)
    guassian_elimination(A, b, u, n);

    // Vi ved at resultatet burde være det samme: 2, -1, 3
    bool passed = true;
    if (!check_approx(u[0], 2.0)) passed = false;
    if (!check_approx(u[1], -1.0)) passed = false;
    if (!check_approx(u[2], 3.0)) passed = false;

    print_result("5.10", passed);

    for (int i = 0; i < n; i++) delete[] A[i];
    delete[] A; delete[] b; delete[] u;
}

int main() {
    std::cout << "========================================\n";
    std::cout << "        KØRER LOKAL CODE CHECKER        \n";
    std::cout << "========================================\n";

    test_2_6();
    test_3_3();
    // test_5_3(); // Tilføj selv hvis du har en test til denne!
    test_5_4();
    test_5_6();
    test_5_9();
    test_5_10();

    std::cout << "========================================\n";
    std::cout << "          ALLE TESTS ER FÆRDIGE         \n";
    std::cout << "========================================\n";

    return 0;
}