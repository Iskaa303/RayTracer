#ifndef PCA_H
#define PCA_H

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <algorithm>

#include "Matrix.h"
#include "Vector.h"
#include "EIG.h"

// Define error codes.
constexpr int PCA_MATRIXNOTSQUARE = -1;
constexpr int PCA_MATRIXNOTSYMMETRIC = -2;

namespace PCA
{

// Function to compute the column means.
template <typename T>
std::vector<T> ComputeColumnMeans(const Matrix2<T> &inputData)
{
	// Determine the size of the input data.
	int numRows = inputData.GetNumRows();
	int numCols = inputData.GetNumCols();
	
	// Create a vector for output.
	std::vector<T> output;	
	
	// Loop through and compute means.
	for (int j=0; j<numCols; ++j)
	{
		T cumulativeSum = static_cast<T>(0.0);
		for (int i=0; i<numRows; ++i)
			cumulativeSum += inputData.GetElement(i,j);
			
		output.push_back(cumulativeSum / static_cast<T>(numRows));
	}
	
	return output;
}

// Function to subtract the column means.
template <typename T>
void SubtractColumnMeans(Matrix2<T> &inputData, std::vector<T> &columnMeans)
{
	// Determine the size of the input data.
	int numRows = inputData.GetNumRows();
	int numCols = inputData.GetNumCols();
	
	// Loop through and subtract the means.
	for (int j=0; j<numCols; ++j)
	{
		for (int i=0; i<numRows; ++i)
			inputData.SetElement(i,j, inputData.GetElement(i,j) - columnMeans.at(j));
	}	
}

// Function to compute the covaraince matrix.
template <typename T>
Matrix2<T> ComputeCovariance(const Matrix2<T> &X)
{
	/* Compute the covariance matrix.
		Note that here we use X'X, rather than XX' as is the usual case.
		This is because we are requiring our data to be arranged with one 
		column (p) for each variable, with one row (k) for each observation. If
		we computed XX', the result would be a [k x k] matrix. The covariance
		matrix should be [p x p], so we need to transpose, hence the use of
		X'X. */
	int numRows = X.GetNumRows();
	Matrix2<T> covX = (static_cast<T>(1.0) / static_cast<T>(numRows - 1)) * (X.Transpose() * X);
	return covX;
}

// Function to compute the eigenvectors of the covariance matrix.
template <typename T>
int ComputeEigenvectors(const Matrix2<T> &covarianceMatrix, Matrix2<T> &eigenvectors)
{
	// Copy the input matrix.
	Matrix2<T> X = covarianceMatrix;

	// The covariance matrix must be square and symmetric.
	if (!X.IsSquare())
		return PCA_MATRIXNOTSQUARE;
		
	// Verify that the matrix is symmetric.
	if (!X.IsSymmetric())
		return PCA_MATRIXNOTSYMMETRIC;
		
	// Compute the eignvalues.
	std::vector<T> eigenValues;
	int returnStatus = EigQR(X, eigenValues);

	// Sort the eigenvalues.
	std::sort(eigenValues.begin(), eigenValues.end());
	std::reverse(eigenValues.begin(), eigenValues.end());

	// Compute the eigenvector for each eigenvalue.
	Vector<T> eV(X.GetNumCols());
	Matrix2<T> eVM(X.GetNumRows(), X.GetNumCols());
	for (int j=0; j<eigenValues.size(); ++j)
	{
		T eig = eigenValues.at(j);
		int returnStatus2 = InvPIt<T>(X, eig, eV);
		for (int i=0; i<eV.GetNumDims(); ++i)
			eVM.SetElement(i, j, eV.GetElement(i));
	}
	
	// Return the eigenvectors.
	eigenvectors = eVM;

	// Return the final return status.	
	return returnStatus;
}

/* Function to compute the principal components of the supplied data. */
template <typename T>
int PCA(const Matrix2<T> &inputData, Matrix2<T> &outputComponents)
{
	// Make a copy of the input matrix.
	Matrix2<T> X = inputData;
	
	// Compute the mean of each column of X.
	std::vector<T> columnMeans = ComputeColumnMeans(X);
	
	// Subtract the column means from the data.
	SubtractColumnMeans<T>(X, columnMeans);
	
	// Compute the covariance matrix.
	Matrix2<T> covX = ComputeCovariance(X);
	
	// Compute the eigenvectors.
	Matrix2<T> eigenvectors;
	int returnStatus = ComputeEigenvectors(covX, eigenvectors);
	
	// Return the output.
	outputComponents = eigenvectors;
	
	return returnStatus;
}

}

#endif
