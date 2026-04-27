
#include <cmath>
#include "Matrix2x2.hpp"


// new constructor for 0 matrix 6.2.1
Matrix2x2::Matrix2x2()
{
		double val00 = 0.0; 
		double val01 = 0.0; 
		double val10 = 0.0; 
		double val11 = 0.0; 
}

// overwritten copy constructor 
Matrix2x2::Matrix2x2(const Matrix2x2& other) 
{
		double val00 = other; 
		double val01 = 0.0; 
		double val10 = 0.0; 
		double val11 = 0.0; 

}



