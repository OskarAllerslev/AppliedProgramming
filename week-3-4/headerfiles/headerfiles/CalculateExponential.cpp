

#include "ComplexNumber.hpp"

/*
calculate matrix exponential of complex matrix

\sum_{n=0}^nmax A^n / n!

we are asked to allocate memory dynamically for a 3x3.

We should store the result in the pointer to res
*/
void CalculateExponential(ComplexNumber **A, int nMax, ComplexNumber **res) {
  // we create a tmp 3x3 matrix
  ComplexNumber **tmp = new ComplexNumber *[3];

  for (int i = 0; i < 3; i++) {
    tmp[i] = new ComplexNumber[3];
  }
  // current term in the sum
  ComplexNumber **current_term = new ComplexNumber *[3];

  for (int i = 0; i < 3; i++) {
    current_term[i] = new ComplexNumber[3];
  }
  /*
  there are three things to do. one where we have the start condition
  next we should do the sum of (T_{n-1} A 1/n) which entails matrix
  multiplication and then we scale
  */
  // create identity matrix
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (row == col) {
        current_term[row][col] = ComplexNumber(1.0, 0.0);
        res[row][col] = ComplexNumber(1.0, 0.0);
      } else {
        current_term[row][col] = ComplexNumber(0.0, 0.0);
        res[row][col] = ComplexNumber(0.0, 0.0);
      }
    }
  }

  // now we do the loop from n =1 to nmax

  for (int n = 1; n <= nMax; n++) {
    // matrix multiplication for Tmp_n = Tmp_{n-1} + (current_term * A)
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        // these two loops just act as the coordinates in the matrix result
        // the below here is C_{ik} A_{kj} (sum over k)
        tmp[i][j] = ComplexNumber(0.0, 0.0);
        for (int k = 0; k < 3; k++) {
          tmp[i][j] = tmp[i][j] + (current_term[i][k] * A[k][j]);
        }
      }
    }
    // matrix x scalar mul for Tmp_n * 1/n for each entry
    // create a new complex number for 1/n
    ComplexNumber scalar(1.0 / n, 0.0);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        current_term[i][j] = tmp[i][j] * scalar;
        res[i][j] = res[i][j] + current_term[i][j];
      }
    }
  }
  // we now delete the tmp and current_term matrixes
  for (int i=0; i<3;i++) 
  {
      delete[] tmp[i];
      delete[] current_term[i];
  }

  delete[] tmp;
  delete[] current_term;

}