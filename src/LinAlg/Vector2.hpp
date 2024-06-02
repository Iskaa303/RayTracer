#ifndef VECTOR2_H
#define VECTOR2_H

/* *************************************************************************************************

	Vector2
	
	Class to provide capability to handle two-dimensional vectors.
************************************************************************************************* */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <memory>
#include "Vector.h"

template <class T>
class Vector2
{
	public:
		// Define the various constructors.
		// Default.
		Vector2();
		
		// With input data (std::vector).
		Vector2(const std::vector<T> &inputData);
		// With input data (Vector).
		Vector2(const Vector<T> &inputData);
		// With input data (Vector2).
		Vector2(const Vector2<T> &inputData);
		// With input data as two separate values.
		Vector2(const T x, const T y);
		
		// And the destructor.
		~Vector2();	
		
		// Keep the GetNumDims() function for backwards compatibility.
		int GetNumDims() const;
		T GetElement(int index) const;
		void SetElement(int index, T value);		
		
		// Functions to perform computations on the vector.
		// Return the length of the vector.
		T norm();
		
		// Return a normalized copy of the vector.
		Vector2<T> Normalized();
		
		// Normalize the vector in place.
		void Normalize();
		
		// Overloaded operators.
		Vector2<T> operator+ (const Vector2<T> &rhs) const;		
		Vector2<T> operator- (const Vector2<T> &rhs) const;
		Vector2<T> operator* (const T &rhs) const;
		
		// Overload the assignment operator.
		Vector2<T> operator= (const Vector<T> &rhs);
		Vector2<T> operator= (const std::vector<T> &rhs);
		Vector2<T> operator= (const Vector2<T> &rhs);
		
		// Friend functions.
		template <class U> friend Vector2<U> operator* (const U &lhs, const Vector2<U> &rhs);
		
		// Static functions.
		static T dot(const Vector2<T> &a, const Vector2<T> &b);
		
	public:
		T m_x;
		T m_y;
		
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Vector2<T>::Vector2()
{
	m_x = static_cast<T>(0.0);
	m_y = static_cast<T>(0.0);
}

template <class T>
Vector2<T>::Vector2(const std::vector<T> &inputData)
{
	if (inputData.size() != 2)
		throw std::invalid_argument("Cannot assign std::vector to Vector2 - assignment dimension mismatch.");
		
	m_x = inputData.at(0);
	m_y = inputData.at(1);
}

template <class T>
Vector2<T>::Vector2(const Vector<T> &inputData)
{
	if (inputData.GetNumDims() != 2)
		throw std::invalid_argument("Cannot assign Vector to Vector2 - assignment dimension mismatch.");
		
	m_x = inputData.GetElement(0);
	m_y = inputData.GetElement(1);
}

template <class T>
Vector2<T>::Vector2(const Vector2<T> &inputData)
{
	m_x = inputData.m_x;
	m_y = inputData.m_y;
}

template <class T>
Vector2<T>::Vector2(const T x, const T y)
{
	m_x = x;
	m_y = y;
}

template <class T>
Vector2<T>::~Vector2()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector, known as the 'norm'.
template <class T>
T Vector2<T>::norm()
{		
	return sqrt((m_x*m_x) + (m_y*m_y));
}

// Return a normalized copy of the vector.
template <class T>
Vector2<T> Vector2<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	// Compute the normalized version of the vector.
	//Vector<T> result(m_vectorData);
	Vector2<T> result;
	result.m_x = m_x / vecNorm;
	result.m_y = m_y / vecNorm;

	return result;
}

// Normalize the vector in place.
template <class T>
void Vector2<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	T denominator = static_cast<T>(1.0) / vecNorm;
	
	m_x = m_x / denominator;
	m_y = m_y / denominator;
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
Vector2<T> Vector2<T>::operator+ (const Vector2<T> &rhs) const
{
	Vector2<T> result;
	result.m_x = m_x + rhs.m_x;
	result.m_y = m_y + rhs.m_y;
	
	return result;
}

template <class T>
Vector2<T> Vector2<T>::operator- (const Vector2<T> &rhs) const
{
	Vector2<T> result;
	result.m_x = m_x - rhs.m_x;
	result.m_y = m_y - rhs.m_y;
	
	return result;
}

template <class T>
Vector2<T> Vector2<T>::operator* (const T &rhs) const
{
	Vector2<T> result;
	result.m_x = m_x * rhs;
	result.m_y = m_y * rhs;
	
	return result;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
Vector2<T> Vector2<T>::operator= (const Vector<T> &rhs)
{
	if (rhs.GetNumDims() != 2)
		throw std::invalid_argument("Cannot assign Vector to Vector2 - assignment dimension mismatch.");
	
	m_x = rhs.GetElement(0);
	m_y = rhs.GetElement(1);
	
	return *this;
}

template <class T>
Vector2<T> Vector2<T>::operator= (const std::vector<T> &rhs)
{
	if (rhs.size() != 2)
		throw std::invalid_argument("Cannot assign std::vector to Vector2 - assignment dimension mismatch.");
	
	m_x = rhs.at(0);
	m_y = rhs.at(1);
	
	return *this;
}

template <class T>
Vector2<T> Vector2<T>::operator= (const Vector2<T> &rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	
	return *this;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
Vector2<T> operator* (const T &lhs, const Vector2<T> &rhs)
{
	// Perform scalar multiplication.
	Vector2<T> result;
	result.m_x = lhs * rhs.m_x;
	result.m_y = lhs * rhs.m_y;
		
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Vector2<T>::dot(const Vector2<T> &a, const Vector2<T> &b)
{
	T cumulativeSum = (a.m_x * b.m_x) + (a.m_y * b.m_y);
	
	return cumulativeSum;
}

/* **************************************************************************************************
FUNCTIONS FOR COMPATIBILITY
/* *************************************************************************************************/
template <class T>
int Vector2<T>::GetNumDims() const
{
	return 2;
}

template <class T>
T Vector2<T>::GetElement(int index) const
{
	if (index == 0)
	{
		return m_x;
	}
	else if (index == 1)
	{
		return m_y;
	}
	else
	{
		throw std::invalid_argument("Attempt to get invalid element index.");
	}
	return 0;
}

template <class T>
void Vector2<T>::SetElement(int index, T value)
{
	if (index == 0)
	{
		m_x = value;
	}
	else if (index == 1)
	{
		m_y = value;
	}
	else
	{
		throw std::invalid_argument("Attempt to set invalid element index.");
	}
}

#endif
