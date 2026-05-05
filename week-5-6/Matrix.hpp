#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"
#include <vector>

template <typename T> class Matrix
{
private:
    std::vector<T> mData;
	int mNumRows, mNumCols; // dimensions

public:
    // we can remove since vector already has copy 
    // copy constructor
	// Matrix(const Matrix& otherMatrix)
    // {
    //     mNumRows = otherMatrix.mNumRows;
    //     mNumCols = otherMatrix.mNumCols;
    //     mData = new double* [mNumRows];

    //     for (int i = 0; i < mNumRows; i++)
    //     {
    //         mData[i] = new double [mNumCols];
    //     }
    //     for (int i = 0; i < mNumRows; i++)
    //     {
    //         for (int j = 0; j < mNumCols; j++)
    //         {
    //             mData[i][j] = otherMatrix.mData[i][j];
    //         }
    //     }
    // }

	Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols)
    {
        assert(numRows > 0);
        assert(numCols > 0);
        mData = std::vector<T>(mNumRows * mNumCols, T(0));
    }

    // we can remove since the vector type already has automatic deletion
	// ~Matrix()
    // {
    //     for (int i = 0; i < mNumRows; i++)
    //     {
    //         delete[] mData[i];
    //     }
    //     delete[] mData;
    // }

	int GetNumberOfRows() const
    {
        return mNumRows;
    }

	int GetNumberOfColumns() const
    {
        return mNumCols;
    }

	T& operator()(int i, int j)
    {
        // we store the matrix in a long vector format 
        assert(i >= 0 && i < mNumRows);
        assert(j >= 0 && j < mNumCols);
        return mData[i * mNumCols  + j];

    }

	T const& operator()(int i, int j) const
    {

        // we store the matrix in a long vector format 
        assert(i >= 0 && i < mNumRows);
        assert(j >= 0 && j < mNumCols);
        return mData[i * mNumCols  + j];

    }

	// overloaded assignment operator
    // i dont think we need this?
	// Matrix& operator=(const Matrix& otherMatrix)
    // {
    //     assert(mNumRows == otherMatrix.mNumRows);
    //     assert(mNumCols == otherMatrix.mNumCols);

    //     for (int i = 0; i < mNumRows; i++)
    //     {
    //         for (int j = 0; j < mNumCols; j++)
    //         {
    //             mData[i][j] = otherMatrix.mData[i][j];
    //         }
    //     }
    //     return *this;
    // }

	Matrix operator-() const // unary -
    {
        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = -(*this)(i,j);
            }
        }
        return mat;
    }

	Matrix operator+(const Matrix& m1) const // binary +
    {
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = (*this)(i,j) + m1(i,j);
            }
        }
        return mat;
    }

	Matrix operator-(const Matrix& m1) const // binary -
    {
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = (*this)(i,j) - m1(i,j);
            }
        }
        return mat;
    }

	// scalar multiplication
	Matrix operator*(T a) const
    {
        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = a* (*this)(i,j);
            }
        }
        return mat;
    }

    std::vector<T> const& getStorage() const 
    {
        return mData;
    }


}; // class Matrix


//matrix-vector multiplications
template <typename T>
Vector<T> operator*(const Matrix<T>& m, const Vector<T>& v)
{
    int original_vector_size = v.size();
	assert(m.GetNumberOfColumns() == original_vector_size);

	int new_vector_length = m.GetNumberOfRows();
	Vector<T> new_vector(new_vector_length);

	for (int i = 0; i < new_vector_length; i++)
	{
		for (int j = 0; j < original_vector_size; j++)
		{
			new_vector[i] += m(i,j)*v[j];
		}
	}

	return new_vector;
}

template <typename T>
Vector<T> operator*(const Vector<T>& v, const Matrix<T>& m)
{
	int original_vector_size = v.size();
	assert(m.GetNumberOfRows() == original_vector_size);

	int new_vector_length = m.GetNumberOfColumns();
	Vector<T> new_vector(new_vector_length);

	for (int i = 0; i < new_vector_length; i++)
	{
		for (int j = 0; j < original_vector_size; j++)
		{
			new_vector[i] += v[j]*m(j,i);
		}
	}

	return new_vector;
}



#endif
