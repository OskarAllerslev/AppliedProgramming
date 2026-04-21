

/*
6 1 0 | 1
5 0 0 | 1
0 0 1 | 1

pr = 1 & col = 0


1 0 0 | 1/5
0 1 0 | 4/5
0 0 1 | 1




*/
#include <algorithm>
#include <cmath>

void guassian_elimination(double **A, double *b, double *u, int n) {

  // we search for the largest row entry in a given column

  for (int col = 0; col < n; col++) {

    int pivot_row = col;
    double max_row_entry = std::abs(A[col][col]);

    for (int row = col + 1; row < n; row++) {
      // find max row entry

      if (std::abs(A[row][col]) > max_row_entry) {
        pivot_row = row;
        max_row_entry = std::abs(A[row][col]);
      }
    }
    // if pivot_row != col then swap pivot
    if (pivot_row != col) {
      std::swap(A[col], A[pivot_row]);
      std::swap(b[col], b[pivot_row]);
    }

    // proceed with gauss elimination
    for (int row = col + 1; row < n; row++) {
      double m_ik = A[row][col] / A[col][col];
      for (int j = col; j < n; j++) {
        A[row][j] = A[row][j] - m_ik * A[col][j];
      }
      b[row] = b[row] - m_ik * b[col];
    }
  }
  // backwards substitution
  for (int i = n - 1; i >= 0; i--) {
    double sum = b[i];
    for (int j = i+ 1; j < n; j++) {
      sum = sum - A[i][j] * u[j];
    }
    u[i] = sum / A[i][i];
  }
}