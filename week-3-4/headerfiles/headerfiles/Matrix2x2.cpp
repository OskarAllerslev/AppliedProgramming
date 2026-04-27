
#include <cassert>
#include <cmath>
#include "Matrix2x2.hpp"


// new constructor for 0 matrix 6.2.1
Matrix2x2::Matrix2x2()
{
		val00 = 0.0; 
		val01 = 0.0; 
		val10 = 0.0; 
		val11 = 0.0; 
}

// overwritten copy constructor 
Matrix2x2::Matrix2x2(const Matrix2x2& other) 
{
		val00 = other.val00; 
		val01 = other.val01; 
		val10 = other.val10; 
		val11 = other.val11; 
}

// constructor that specifies four entries and allocates these
Matrix2x2::Matrix2x2(double a, double b, double c, double d)
{
	val00 = a;
	val01 = b;
	val10 = c;
	val11 = d;
}


// function for calculating determinant for 2x2 matrix
double Matrix2x2::CalcDeterminant() const
{
	// we can just get the entries directly 
	return val00 * val11 - val01 * val10;
}


// functionf or calculating inverse if exists
Matrix2x2 Matrix2x2::CalcInverse() const
{
	// we can just use [ d - b ][-c a ] * 1/det(A)
	// we need det(A) =! 0
	double determinant = CalcDeterminant();
	assert(determinant != 0);
	double new_00 = val11 / determinant;
	double new_01 = -val01 / determinant;
	double new_10 = -val10 / determinant;
	double new_11 = val00 / determinant;
	return Matrix2x2(new_00, new_01, new_10, new_11);
}