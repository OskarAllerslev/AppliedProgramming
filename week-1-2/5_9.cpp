#include <cassert>


// function for calculating the determinant of a 3x3 matrix
double CalcDet3by3(double **M)
{
  double det = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
               M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
               M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
  return det;
}


void solve3by3(
    double **A, 
    double *b, 
    double *u
){
    // we use cramers rule to find solutions given by x_i = det(A_i) / det(A) where A_i is A but replaced by the b vector
    double det_A = CalcDet3by3(A);
    assert(det_A != 0.0);
   


    // we need to create three new matrices  
    for (int i = 0; i < 3; i++)
    {
        double **tmpMatrix = new double*[3]; // create new matrix on the heap here
        // we need to create the inner layer of structure that we need on the above object
        for (int row=0; row<3; row++)
        {
            tmpMatrix[row] = new double[3];
        }        


        // we need to copy the contents of A over to the new matrix 
        for (int row = 0; row <3; row++) 
        {
            for (int col=0; col<3; col++)
            {
                tmpMatrix[row][col] = A[row][col];
            }
        }

        // overwrite the i'th column
        for (int row = 0; row < 3; row++)
        {
            tmpMatrix[row][i] = b[row];
        }

        // now we need the determinant 
        u[i] = CalcDet3by3(tmpMatrix) / det_A;


        // clean the memory from the heap
        for (int row = 0; row < 3; row++) 
        {
            delete[] tmpMatrix[row];
        }
        delete[] tmpMatrix;


    }
    
}