
#include <iostream>
// #include "2_6.h"
// #include "3_3.h"
// #include "5_4.h"
// #include "5_6.h"
#include "5_9.h"

int main() {
  // double f_val = f_x(0.0);
  // double f_prime_val = f_prime_x(0.0);
  // std::cout << "f value in 0 " << f_val << std::endl;
  // std::cout << "f prime  value in 0 " << f_prime_val << std::endl;
  // double initial_guess = 2;
  // double epsilon = 0.000001;
  // double NR = newton_Raphson(initial_guess,epsilon);
  // std::cout << "newton raphson i " << initial_guess << " resultere i " << NR
  // << std::endl;

  // int n = 100;
  // implicit_Euler(n);
  // std::cout << "tjek om der er en data fil" << std::endl;

  // double test_array[4] = {1.0, 2.0, 9.0, 7.8};
  // double std_err = calc_std(test_array, 4);

  // std::cout << "the standard error of our array: " << *test_array << "\n"
  // << " is " << std_err << std::endl;

  // test af matrix scipt
  // double A_data[2][2] = {{1, 2}, {3, 4}};
  // double B_data[2][2] = {{1, 2}, {3, 4}};
  // double res_data[2][2];

  // double *A[2] = {A_data[0], A_data[1]};
  // double *B[2] = {B_data[0], B_data[1]};
  // double *res[2] = {res_data[0], res_data[1]};

  // Multiply(res, A, B, 2, 2, 2, 2);

  // std::cout << "Resultat:\n";
  // std::cout << res[0][0] << " " << res[0][1] << "\n";
  // std::cout << res[1][0] << " " << res[1][1] << "\n";


  // test af 5.9
  double **A = new double*[3];
  for (int i = 0; i<3; i++)
  {
    A[i] = new double[3];
  }
  double *b = new double[3];
  double *u = new double[3];

  b[0] = 9;
  b[1] = 8;
  b[2] = 3;
  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 2;
  A[1][1] = -1;
  A[1][2] = 1;
  A[2][0] = 3;
  A[2][1] = 0;
  A[2][2] = -1;
  

  solve3by3(A, b, u);

  std::cout << "Løsningen af vores ligningssystem: " << 
  u[0]  << " " << 
  u[1]  << " " << 
  u[2]  << " " << 
  std::endl; 

  for (int i = 0; i<3;i++)
  {
    delete[] A[i];
  }
  delete[] A;
  delete[] b;
  delete[] u;


  return 0;
}
