#ifndef Vector4_H
#define Vector4_H

/* *************************************************************************************************

	Vector4
	
	Class to provide capability to handle four-dimensional vectors.					

************************************************************************************************* */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <memory>
#include "Vector.h"

template <class T>
class Vector4
{
	public:
		// Define the various constructors.
		// Default.
		Vector4();
		
		// With input data (std::vector).
		Vector4(const std::vector<T> &inputData);
		// With input data (Vector).
		Vector4(const Vector<T> &inputData);
		// With input data (Vector4).
		Vector4(const Vector4<T> &inputData);
		// With input data as four separate values.
		Vector4(const T v1, const T v2, const T v3, const T v4);
		
		// And the destructor.
		~Vector4();	
		
		// Keep the GetNumDims() function for backwards compatibility.
		int GetNumDims() const;
		T GetElement(int index) const;
		void SetElement(int index, T value);		
		
		// Functions to perform computations on the vector.
		// Return the length of the vector.
		T norm();
		
		// Return a normalized copy of the vector.
		Vector4<T> Normalized();
		
		// Normalize the vector in place.
		void Normalize();
		
		// Overloaded operators.
		Vector4<T> operator+ (const Vector4<T> &rhs) const;		
		Vector4<T> operator- (const Vector4<T> &rhs) const;
		Vector4<T> operator* (const T &rhs) const;
		
		// Overload the assignment operator.
		Vector4<T> operator= (const Vector<T> &rhs);
		Vector4<T> operator= (const std::vector<T> &rhs);
		Vector4<T> operator= (const Vector4<T> &rhs);
		
		// Friend functions.
		template <class U> friend Vector4<U> operator* (const U &lhs, const Vector4<U> &rhs);
		
		// Static functions.
		static T dot(const Vector4<T> &a, const Vector4<T> &b);
		
	public:
		T m_v1;
		T m_v2;
		T m_v3;
		T m_v4;
		
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Vector4<T>::Vector4()
{
	m_v1 = static_cast<T>(0.0);
	m_v2 = static_cast<T>(0.0);
	m_v2 = static_cast<T>(0.0);
	m_v4 = static_cast<T>(0.0);
}

template <class T>
Vector4<T>::Vector4(const std::vector<T> &inputData)
{
	if (inputData.size() != 4)
		throw std::invalid_argument("Cannot assign std::vector to Vector4 - assignment dimension mismatch.");
		
	m_v1 = inputData.at(0);
	m_v2 = inputData.at(1);
	m_v3 = inputData.at(2);
	m_v4 = inputData.at(3);
}

template <class T>
Vector4<T>::Vector4(const Vector<T> &inputData)
{
	if (inputData.GetNumDims() != 4)
		throw std::invalid_argument("Cannot assign Vector to Vector4 - assignment dimension mismatch.");
		
	m_v1 = inputData.GetElement(0);
	m_v2 = inputData.GetElement(1);
	m_v2 = inputData.GetElement(2);
	m_v3 = inputData.GetElement(3);
	
}

template <class T>
Vector4<T>::Vector4(const Vector4<T> &inputData)
{
	m_v1 = inputData.m_v1;
	m_v2 = inputData.m_v2;
	m_v3 = inputData.m_v3;
	m_v4 = inputData.m_v4;
}

template <class T>
Vector4<T>::Vector4(const T v1, const T v2, const T v3, const T v4)
{
	m_v1 = v1;
	m_v2 = v2;
	m_v3 = v3;
	m_v4 = v4;
}

template <class T>
Vector4<T>::~Vector4()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector, known as the 'norm'.
template <class T>
T Vector4<T>::norm()
{		
	return sqrt((m_v1*m_v1) + (m_v2*m_v2) + (m_v3*m_v3) + (m_v4*m_v4));
}

// Return a normalized copy of the vector.
template <class T>
Vector4<T> Vector4<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	// Compute the normalized version of the vector.
	//Vector<T> result(m_vectorData);
	Vector4<T> result;
	result.m_v1 = m_v1 / vecNorm;
	result.m_v2 = m_v2 / vecNorm;
	result.m_v3 = m_v3 / vecNorm;
	result.m_v4 = m_v4 / vecNorm;

	return result;
}

// Normalize the vector in place.
template <class T>
void Vector4<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	T denominator = static_cast<T>(1.0) / vecNorm;
	
	m_v1 = m_v1 / denominator;
	m_v2 = m_v2 / denominator;
	m_v3 = m_v3 / denominator;
	m_v4 = m_v4 / denominator;
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
Vector4<T> Vector4<T>::operator+ (const Vector4<T> &rhs) const
{
	Vector4<T> result;
	result.m_v1 = m_v1 + rhs.m_v1;
	result.m_v2 = m_v2 + rhs.m_v2;
	result.m_v3 = m_v3 + rhs.m_v3;
	result.m_v4 = m_v4 + rhs.m_v4;
	
	return result;
}

template <class T>
Vector4<T> Vector4<T>::operator- (const Vector4<T> &rhs) const
{
	Vector4<T> result;
	result.m_v1 = m_v1 - rhs.m_v1;
	result.m_v2 = m_v2 - rhs.m_v2;
	result.m_v3 = m_v3 - rhs.m_v3;
	result.m_v4 = m_v4 - rhs.m_v4;
	
	return result;
}

template <class T>
Vector4<T> Vector4<T>::operator* (const T &rhs) const
{
	Vector4<T> result;
	result.m_v1 = m_v1 * rhs;
	result.m_v2 = m_v2 * rhs;
	result.m_v3 = m_v3 * rhs;
	result.m_v4 = m_v4 * rhs;
	
	return result;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
Vector4<T> Vector4<T>::operator= (const Vector<T> &rhs)
{
	if (rhs.GetNumDims() != 4)
		throw std::invalid_argument("Cannot assign Vector to Vector4 - assignment dimension mismatch.");
	
	m_v1 = rhs.GetElement(0);
	m_v2 = rhs.GetElement(1);
	m_v3 = rhs.GetElement(2);
	m_v4 = rhs.GetElement(3);
	
	return *this;
}

template <class T>
Vector4<T> Vector4<T>::operator= (const std::vector<T> &rhs)
{
	if (rhs.size() != 4)
		throw std::invalid_argument("Cannot assign std::vector to Vector4 - assignment dimension mismatch.");
	
	m_v1 = rhs.at(0);
	m_v2 = rhs.at(1);
	m_v3 = rhs.at(2);
	m_v4 = rhs.at(3);
	
	return *this;
}

template <class T>
Vector4<T> Vector4<T>::operator= (const Vector4<T> &rhs)
{
	m_v1 = rhs.m_v1;
	m_v2 = rhs.m_v2;
	m_v3 = rhs.m_v3;
	m_v4 = rhs.m_v4;
	
	return *this;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
Vector4<T> operator* (const T &lhs, const Vector4<T> &rhs)
{
	// Perform scalar multiplication.
	Vector4<T> result;
	result.m_v1 = lhs * rhs.m_v1;
	result.m_v2 = lhs * rhs.m_v2;
	result.m_v3 = lhs * rhs.m_v3;
	result.m_v4 = lhs * rhs.m_v4;
		
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Vector4<T>::dot(const Vector4<T> &a, const Vector4<T> &b)
{
	T cumulativeSum = (a.m_v1 * b.m_v1) + (a.m_v2 * b.m_v2) + (a.m_v3 * b.m_v3) + (a.m_v4 * b.m_v4);
	
	return cumulativeSum;
}

/* **************************************************************************************************
FUNCTIONS FOR COMPATIBILITY
/* *************************************************************************************************/
template <class T>
int Vector4<T>::GetNumDims() const
{
	return 4;
}

template <class T>
T Vector4<T>::GetElement(int index) const
{
	if (index == 0)
	{
		return m_v1;
	}
	else if (index == 1)
	{
		return m_v2;
	}
	else if (index == 2)
	{
		return m_v3;
	}
	else if (index == 3)
	{
		return m_v4;
	}
	else
	{
		throw std::invalid_argument("Attempt to get invalid element index.");
	}
	return 0;
}

template <class T>
void Vector4<T>::SetElement(int index, T value)
{
	if (index == 0)
	{
		m_v1 = value;
	}
	else if (index == 1)
	{
		m_v2 = value;
	}
	else if (index == 2)
	{
		m_v3 = value;
	}
	else if (index == 3)
	{
		m_v4 = value;
	}
	else
	{
		throw std::invalid_argument("Attempt to set invalid element index.");
	}
}

#endif
