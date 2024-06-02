#ifndef Matrix44_H
#define Matrix44_H

/* *************************************************************************************************
Class to provide capability to handle two-dimensional matrices.
************************************************************************************************* */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <exception>
#include "Vector.h"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix33.hpp"

template <class T>
class Matrix44
{
	public:
		// Define the various constructors.
    Matrix44();
    Matrix44(const Matrix44<T> &inputMatrix);
    Matrix44(const std::vector<T> &inputData);

    // And the destructor.
    ~Matrix44();

    // Configuration methods.
    void SetToIdentity();

    // Element access methods.
    T GetElement(int row, int col) const;
    bool SetElement(int row, int col, T elementValue);
    int GetNumRows() const;
    int GetNumCols() const;
    
    // Manipulation methods.
    // Compute matrix inverse.
    bool Inverse();

    // Return the transpose.
    Matrix44<T> Transpose() const;
    
    // Compute determinant.
    T Determinant();

		// Overload == operator.
		bool operator== (const Matrix44<T>& rhs);
		bool Compare (const Matrix44<T>& matrix1, double tolerance);
		
		// Overload the assignment operator.
		Matrix44<T> operator= (const Matrix44<T> &rhs);

    // Overload +, - and * operators (friends).
    template <class U> friend Matrix44<U> operator+ (const Matrix44<U>& lhs, const Matrix44<U>& rhs);
    template <class U> friend Matrix44<U> operator+ (const U& lhs, const Matrix44<U>& rhs);
    template <class U> friend Matrix44<U> operator+ (const Matrix44<U>& lhs, const U& rhs);
    
    template <class U> friend Matrix44<U> operator- (const Matrix44<U>& lhs, const Matrix44<U>& rhs);
    template <class U> friend Matrix44<U> operator- (const U& lhs, const Matrix44<U>& rhs);
    template <class U> friend Matrix44<U> operator- (const Matrix44<U>& lhs, const U& rhs);
    
    template <class U> friend Matrix44<U> operator* (const Matrix44<U>& lhs, const Matrix44<U>& rhs);
    template <class U> friend Matrix44<U> operator* (const U& lhs, const Matrix44<U>& rhs);
    template <class U> friend Matrix44<U> operator* (const Matrix44<U>& lhs, const U& rhs);
    
    // Matrix44 * Vector4.
    template <class U> friend Vector4<U> operator* (const Matrix44<U>& lhs, const Vector4<U>& rhs);      
    
    Matrix33<T> FindSubMatrix(int rowNum, int colNum);

	private:
		int Sub2Ind(int row, int col) const;
		bool CloseEnough(T f1, T f2);

	public:
		//T *m_matrixData;
		T m_matrixData[16];
    int m_nRows = 4;
    int m_nCols = 4;
    int m_nElements = 16;
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Matrix44<T>::Matrix44()
{

}

// The copy constructor.
template <class T>
Matrix44<T>::Matrix44(const Matrix44<T> &inputMatrix)
{
	for (int i=0; i<16; i++)
		m_matrixData[i] = inputMatrix.m_matrixData[i];
}

// Construct from std::vector.
template <class T>
Matrix44<T>::Matrix44(const std::vector<T> &inputData)
{
	if (inputData.size() != 16)
		throw std::invalid_argument("Cannot assign std::vector to Matrix44 - assignment dimension mismatch.");

	for (int i=0; i<16; ++i)
		m_matrixData[i] = inputData.at(i);
}

template <class T>
Matrix44<T>::~Matrix44()
{

}

/* **************************************************************************************************
CONFIGURATION FUNCTIONS
/* *************************************************************************************************/
// Function to convert the existing matrix into an identity matrix.
template <class T>
void Matrix44<T>::SetToIdentity()
{		
	for (int row=0; row<m_nRows; ++row)
	{
		for (int col=0; col<m_nCols; ++col)
		{
			if (col == row)
				m_matrixData[Sub2Ind(row,col)] = 1.0;
			else
				m_matrixData[Sub2Ind(row,col)] = 0.0;
		}
	}
}

/* **************************************************************************************************
ELEMENT FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Matrix44<T>::GetElement(int row, int col) const
{
	int linearIndex = Sub2Ind(row, col);
	if (linearIndex >= 0)
		return m_matrixData[linearIndex];
	else
		return 0.0;

}

template <class T>
bool Matrix44<T>::SetElement(int row, int col, T elementValue)
{
	int linearIndex = Sub2Ind(row, col);
	if (linearIndex >= 0)
	{
		m_matrixData[linearIndex] = elementValue;
		return true;
	} 
	else 
	{
		return false;
	}
}

template <class T>
int Matrix44<T>::GetNumRows() const
{
	return m_nRows;
}

template <class T>
int Matrix44<T>::GetNumCols() const
{
	return m_nCols;
}

template <class T>
bool Matrix44<T>::Compare(const Matrix44<T>& matrix1, double tolerance)
{
	// First, check that the matrices have the same dimensions.
	int numRows1 = matrix1.m_nRows;
	int numCols1 = matrix1.m_nCols;
	if ((numRows1 != m_nRows) || (numCols1 != m_nCols))
		return false;
		
	// Loop over all the elements and compute the sum-of-squared-differences.
	double cumulativeSum = 0.0;
	for (int i=0; i<m_nElements; ++i)
	{
		T element1 = matrix1.m_matrixData[i];
		T element2 = m_matrixData[i];
		cumulativeSum += ((element1 - element2) * (element1 - element2));
	}
	double finalValue = sqrt(cumulativeSum / ((numRows1 * numCols1)-1));
	if (finalValue < tolerance)
		return true;
	else
		return false;
}

/* **************************************************************************************************
OVERLOADED OPERATOR FUNCTIONS
/* *************************************************************************************************/

/* **************************************************************************************************
THE + OPERATOR
/* *************************************************************************************************/
// matrix + matrx.
template <class T>
Matrix44<T> operator+ (const Matrix44<T>& lhs, const Matrix44<T>& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];

	return result;
}

// scaler + matrix
template <class T>
Matrix44<T> operator+ (const T& lhs, const Matrix44<T>& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs + rhs.m_matrixData[i];

	return result;
}

// matrix + scaler
template <class T>
Matrix44<T> operator+ (const Matrix44<T>& lhs, const T& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs.m_matrixData[i] + rhs;
			
	return result;
}

/* **************************************************************************************************
THE - OPERATOR
/* *************************************************************************************************/
// matrix - matrix
template <class T>
Matrix44<T> operator- (const Matrix44<T>& lhs, const Matrix44<T>& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];

	return result;   
}

// scaler - matrix
template <class T>
Matrix44<T> operator- (const T& lhs, const Matrix44<T>& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs - rhs.m_matrixData[i];

	return result;
}

// matrix - scaler
template <class T>
Matrix44<T> operator- (const Matrix44<T>& lhs, const T& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs.m_matrixData[i] - rhs;
			
	return result;
}

/* **************************************************************************************************
THE * OPERATOR
/* *************************************************************************************************/
// matrix * Vector4
template <class T>
Vector4<T> operator* (const Matrix44<T>& lhs, const Vector4<T>& rhs)
{
	// Setup the vector for the output.
	Vector4<T> result;
	
	// Loop over rows and columns and perform the multiplication operation element-by-element.
	for (int row=0; row<lhs.m_nRows; ++row)
	{
		T cumulativeSum = static_cast<T>(0.0);
		cumulativeSum += (lhs.GetElement(row,0) * rhs.m_v1);
		cumulativeSum += (lhs.GetElement(row,1) * rhs.m_v2);
		cumulativeSum += (lhs.GetElement(row,2) * rhs.m_v3);
		cumulativeSum += (lhs.GetElement(row,3) * rhs.m_v4);

		result.SetElement(row, cumulativeSum);
	}
	
	return result;
}

// scaler * matrix
template <class T>
Matrix44<T> operator* (const T& lhs, const Matrix44<T>& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs * rhs.m_matrixData[i];
			
	return result;
}

// matrix * scaler
template <class T>
Matrix44<T> operator* (const Matrix44<T>& lhs, const T& rhs)
{
	Matrix44<T> result;
	for (int i=0; i<16; ++i)
		result.m_matrixData[i] = lhs.m_matrixData[i] * rhs;
			
	return result;
}

// matrix * matrix
template <class T>
Matrix44<T> operator* (const Matrix44<T>& lhs, const Matrix44<T>& rhs)
{
	int r_numRows = rhs.m_nRows;
	int r_numCols = rhs.m_nCols;
	int l_numRows = lhs.m_nRows;
	int l_numCols = lhs.m_nCols;

	// This is the standard matrix multiplication condition.
	// The output will be the same size as the RHS.
	Matrix44<T> result;

	// Loop through each row of the LHS.
	for (int lhsRow=0; lhsRow<l_numRows; lhsRow++)
	{
		// Loop through each column on the RHS.
		for (int rhsCol=0; rhsCol<r_numCols; rhsCol++)
		{
			T elementResult = static_cast<T>(0.0);
			
			// Loop through each element of this LHS row.
			for (int lhsCol=0; lhsCol<l_numCols; lhsCol++)
			{
				// Compute the LHS linear index.
				int lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;
				
				// Compute the RHS linear index (based on LHS col).
				// rhs row number equal to lhs column number.
				int rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;
				
				// Perform the calculation on these elements.
				elementResult += (lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex]);
			}
			// Store the result.
			int resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
			result.m_matrixData[resultLinearIndex] = elementResult;
		}		
	}
	return result;
}

/* **************************************************************************************************
THE == OPERATOR
/* *************************************************************************************************/
template <class T>
bool Matrix44<T>::operator== (const Matrix44<T>& rhs)
{	
	// Check if the elements are equal.
	bool flag = true;
	for (int i=0; i<16; ++i)
	{
		//if (this->m_matrixData[i] != rhs.m_matrixData[i])
		if (!CloseEnough(this->m_matrixData[i], rhs.m_matrixData[i]))
			flag = false;
	}
	return flag;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
Matrix44<T> Matrix44<T>::operator= (const Matrix44<T> &rhs)
{
	// Make sure we're not assigning to ourself.
	if (this != &rhs)
	{
		for (int i=0; i<m_nElements; ++i)
			m_matrixData[i] = rhs.m_matrixData[i];
	}
	
	return *this;
}

/* **************************************************************************************************
TRANSPOSE
/* *************************************************************************************************/
template <class T>
Matrix44<T> Matrix44<T>::Transpose() const
{
	Matrix44<double> result;

	for (int i=0; i<4; ++i)
	{
		for (int j=0; j<4; ++j)
		{
			result.SetElement(j, i, this->GetElement(i, j));
		}
	}	

	return result;
}

/* **************************************************************************************************
INVERSE
/* *************************************************************************************************/
template <class T>
bool Matrix44<T>::Inverse()
{
	// Construct the adjucate matrix.
	Matrix44<T> adjugate;
	
	int sign = 1;
	int rowSign = 1;
	for (int row=0; row<4; ++row)
	{
		for (int col=0; col<4; ++col)
		{
			Matrix33<T> subMatrix = FindSubMatrix(row, col);
			T subMatrixDeterminant = subMatrix.Determinant();
			adjugate.SetElement(row, col, static_cast<T>(sign) * subMatrixDeterminant);
			sign *= -1;
		}
		rowSign *= -1;
		sign = rowSign;
	}
	
	Matrix44<T> adjT = adjugate.Transpose();
	
	// Compute the inverse.
	T determinant = Determinant();
	if (CloseEnough(determinant, 0.0))
		return false;
			
	Matrix44<T> result = (1.0 / determinant) * adjT;
	
	// And store 'in place'.
	for (int i=0; i<16; ++i)
		m_matrixData[i] = result.m_matrixData[i];
	
	return true;
}

/* **************************************************************************************************
DETERMINANT
/* *************************************************************************************************/
template <class T>
T Matrix44<T>::Determinant()
{
	T cumulativeSum = static_cast<T>(0.0);
	int sign = 1;

	int row = 0;
	for (int col=0; col<4; ++col)
	{
		Matrix33<T> subMatrix = FindSubMatrix(row, col);
		T subMatrixDeterminant = subMatrix.Determinant();
		cumulativeSum += (static_cast<T>(sign) * GetElement(row, col) * subMatrixDeterminant);
		sign *= -1;
	}

	return cumulativeSum;
}

/* **************************************************************************************************
PRIVATE FUNCTIONS
/* *************************************************************************************************/
// Function to return the linear index corresponding to the supplied row and column values.
template <class T>
int Matrix44<T>::Sub2Ind(int row, int col) const
{
	if ((row < m_nRows) && (row >= 0) && (col < m_nCols) && (col >= 0))
		return (row * m_nCols) + col;
	else
		return -1;
}

// Function to find the sub-matrix for the given element.
template <class T>
Matrix33<T> Matrix44<T>::FindSubMatrix(int rowNum, int colNum)
{
	// Create a new matrix to store the sub-matrix.
	// Note that this is one row and one column smaller than the original.
	Matrix33<T> subMatrix;
	
	// Loop over the elements of the existing matrix and copy to sub-matrix as appropriate.
	int count = 0;
	for (int i=0; i<m_nRows; ++i)
	{
		for (int j=0; j<m_nCols; ++j)
		{
			// If i or j correspond to rowNum or colNum, then ignore this element.
			if ((i != rowNum) && (j != colNum))
			{
				subMatrix.m_matrixData[count] = this->GetElement(i,j);
				count++;
			}
		}
	}
	
	return subMatrix;
}

template <class T>
bool Matrix44<T>::CloseEnough(T f1, T f2)
{
    return fabs(f1-f2) < 1e-9;
}

#endif
