#include <cassert>


void Multiply(
    double **res, 
    double **A, 
    double **B, 
    int ARows, 
    int ACols, 
    int BRows, 
    int BCols
){
    assert(ACols == BRows);

    for (int i = 0; i < ARows; i++) 
    {
        for (int j = 0; j < BCols; j++) 
        {
            res[i][j] = 0.0;
            // now we actually calculate the sum product of each of the entries 
            for (int k = 0; k < ACols; k++) 
            {
               res[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// vector times matrix 
void Multiply(
    double *res, 
    double *A, 
    double **B, 
    int ACols, 
    int BRows, 
    int BCols
){
    assert(ACols == BRows);

    for (int i = 0; i < BCols; i++)
    {
        res[i] = 0.0;
        for(int j = 0; j < ACols; j++)
        {
            res[i] += A[j] * B[j][i];
        }
    }
}







void Multiply(double *res, double **A, double *B, int ARows, int ACols, int BRows);
void Multiply(double **res, double scalar, double **B, int BRows, int BCols) ;
void Multiply(double **res, double **B, double scalar, int BRows, int BCols) ;