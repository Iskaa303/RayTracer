#ifndef LSQ_H
#define LSQ_H

/* *************************************************************************************************

	LSQ
	
	Function to solve a system of linear equations using a least squares approach to handle systems
	where there are more equations (observations) than unknowns. Assumes that the system is in the
	form of y = X*beta.
	
	*** INPUTS ***
	
	Xin		Matrix2<T>		The matrix of independent variables (X in the above equation).
	yin		Vector<T>		The vector of dependent variables (y in the above equation).
	result		Vector<T>		The vector of unknown parameters (beta in the above equation).
						The final solution is returned in this vector.
															
	*** OUTPUTS ***
	
	INT				Flag indicating success or failure of the process.
						1 Indicates success.
						-1 indicates failure due to there being no computable inverse.			

	************************************************************************************************* */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include "Vector.h"
#include "Matrix.h"

// Define error codes.
constexpr int LSQ_NOINVERSE = -1;

// The LSQ function.
template <typename T>
int LSQ(const Matrix2<T> &Xin, const Vector<T> &yin, Vector<T> &result)
{
	// Firstly, make a copy of X and y.
	Matrix2<T> X = Xin;
	Vector<T> y = yin;
	
	// Compute the tranpose of X.
	Matrix2<T> XT = X.Transpose();
	
	// Compute XTX.
	Matrix2<T> XTX = XT * X;
	
	// Compute the inverse of this.
	if (!XTX.Inverse())
	{
		// We were unable to compute the inverse.
		return LSQ_NOINVERSE;
	}
	
	// Multiply the inverse by XT.
	Matrix2<T> XTXXT = XTX * XT;
	
	// And multiply by y to get the final result.
	result = XTXXT * y;
	
	return 1;
}

#endif
