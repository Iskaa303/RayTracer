#ifndef VECTOR3_H
#define VECTOR3_H

/* *************************************************************************************************

	Vector3
	
	Class to provide capability to handle three-dimensional vectors.					

************************************************************************************************* */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <memory>
#include "Vector.h"

template <class T>
class Vector3
{
	public:
		// Define the various constructors.
		// Default.
		Vector3();
		
		// With input data (std::vector).
		Vector3(const std::vector<T> &inputData);
		// With input data (Vector).
		Vector3(const Vector<T> &inputData);
		// With input data (Vector3).
		Vector3(const Vector3<T> &inputData);
		// With input data as three separate values.
		Vector3(const T x, const T y, const T z);
		
		// And the destructor.
		~Vector3();	
		
		// Keep the GetNumDims() function for backwards compatibility.
		int GetNumDims() const;
		T GetElement(int index) const;
		void SetElement(int index, T value);		
		
		// Functions to perform computations on the vector.
		// Return the length of the vector.
		T norm();
		
		// Return a normalized copy of the vector.
		Vector3<T> Normalized();
		
		// Normalize the vector in place.
		void Normalize();
		
		// Overloaded operators.
		Vector3<T> operator+ (const Vector3<T> &rhs) const;		
		Vector3<T> operator- (const Vector3<T> &rhs) const;
		Vector3<T> operator* (const T &rhs) const;
		
		// Overload the assignment operator.
		Vector3<T> operator= (const Vector<T> &rhs);
		Vector3<T> operator= (const std::vector<T> &rhs);
		Vector3<T> operator= (const Vector3<T> &rhs);
		
		// Friend functions.
		template <class U> friend Vector3<U> operator* (const U &lhs, const Vector3<U> &rhs);
		
		// Static functions.
		static T dot(const Vector3<T> &a, const Vector3<T> &b);
		static Vector3<T> cross(const Vector3<T> &a, const Vector3<T> &b);
		
	public:
		T m_x;
		T m_y;
		T m_z;
		
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
Vector3<T>::Vector3()
{
	m_x = static_cast<T>(0.0);
	m_y = static_cast<T>(0.0);
	m_z = static_cast<T>(0.0);
}

template <class T>
Vector3<T>::Vector3(const std::vector<T> &inputData)
{
	if (inputData.size() != 3)
		throw std::invalid_argument("Cannot assign std::vector to Vector3 - assignment dimension mismatch.");
		
	m_x = inputData.at(0);
	m_y = inputData.at(1);
	m_z = inputData.at(2);
}

template <class T>
Vector3<T>::Vector3(const Vector<T> &inputData)
{
	if (inputData.GetNumDims() != 3)
		throw std::invalid_argument("Cannot assign Vector to Vector3 - assignment dimension mismatch.");
		
	m_x = inputData.GetElement(0);
	m_y = inputData.GetElement(1);
	m_z = inputData.GetElement(2);
}

template <class T>
Vector3<T>::Vector3(const Vector3<T> &inputData)
{
	m_x = inputData.m_x;
	m_y = inputData.m_y;
	m_z = inputData.m_z;
}

template <class T>
Vector3<T>::Vector3(const T x, const T y, const T z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

template <class T>
Vector3<T>::~Vector3()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector, known as the 'norm'.
template <class T>
T Vector3<T>::norm()
{		
	return sqrt((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
}

// Return a normalized copy of the vector.
template <class T>
Vector3<T> Vector3<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	// Compute the normalized version of the vector.
	//Vector<T> result(m_vectorData);
	Vector3<T> result;
	result.m_x = m_x / vecNorm;
	result.m_y = m_y / vecNorm;
	result.m_z = m_z / vecNorm;

	return result;
}

// Normalize the vector in place.
template <class T>
void Vector3<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	m_x = m_x / vecNorm;
	m_y = m_y / vecNorm;
	m_z = m_z / vecNorm;
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
Vector3<T> Vector3<T>::operator+ (const Vector3<T> &rhs) const
{
	Vector3<T> result;
	result.m_x = m_x + rhs.m_x;
	result.m_y = m_y + rhs.m_y;
	result.m_z = m_z + rhs.m_z;
	
	return result;
}

template <class T>
Vector3<T> Vector3<T>::operator- (const Vector3<T> &rhs) const
{
	Vector3<T> result;
	result.m_x = m_x - rhs.m_x;
	result.m_y = m_y - rhs.m_y;
	result.m_z = m_z - rhs.m_z;
	
	return result;
}

template <class T>
Vector3<T> Vector3<T>::operator* (const T &rhs) const
{
	Vector3<T> result;
	result.m_x = m_x * rhs;
	result.m_y = m_y * rhs;
	result.m_z = m_z * rhs;
	
	return result;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
Vector3<T> Vector3<T>::operator= (const Vector<T> &rhs)
{
	if (rhs.GetNumDims() != 3)
		throw std::invalid_argument("Cannot assign Vector to Vector3 - assignment dimension mismatch.");
	
	m_x = rhs.GetElement(0);
	m_y = rhs.GetElement(1);
	m_z = rhs.GetElement(2);
	
	return *this;
}

template <class T>
Vector3<T> Vector3<T>::operator= (const std::vector<T> &rhs)
{
	if (rhs.size() != 3)
		throw std::invalid_argument("Cannot assign std::vector to Vector3 - assignment dimension mismatch.");
	
	m_x = rhs.at(0);
	m_y = rhs.at(1);
	m_z = rhs.at(2);
	
	return *this;
}

template <class T>
Vector3<T> Vector3<T>::operator= (const Vector3<T> &rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_z = rhs.m_z;
	
	return *this;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
Vector3<T> operator* (const T &lhs, const Vector3<T> &rhs)
{
	// Perform scalar multiplication.
	Vector3<T> result;
	result.m_x = lhs * rhs.m_x;
	result.m_y = lhs * rhs.m_y;
	result.m_z = lhs * rhs.m_z;
		
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T Vector3<T>::dot(const Vector3<T> &a, const Vector3<T> &b)
{
	T cumulativeSum = (a.m_x * b.m_x) + (a.m_y * b.m_y) + (a.m_z * b.m_z);
	
	return cumulativeSum;
}

template <class T>
Vector3<T> Vector3<T>::cross(const Vector3<T> &a, const Vector3<T> &b)
{
	// Compute the cross product.
	Vector3<T> result;
	result.SetElement(0, ((a.GetElement(1) * b.GetElement(2)) - (a.GetElement(2) * b.GetElement(1))));
	result.SetElement(1, (-((a.GetElement(0) * b.GetElement(2)) - (a.GetElement(2) * b.GetElement(0)))));
	result.SetElement(2, ((a.GetElement(0) * b.GetElement(1)) - (a.GetElement(1) * b.GetElement(0))));		
	//result.m_x = (a.m_y * b.m_z) - (a.m_z * b.m_y);
	//result.m_y = -((a.m_x * b.m_z) - (a.m_z * b.m_x));
	//result.m_z = (a.m_x * b.m_y) - (a.m_y * b.m_x);
	
	return result;
}

/* **************************************************************************************************
FUNCTIONS FOR COMPATIBILITY
/* *************************************************************************************************/
template <class T>
int Vector3<T>::GetNumDims() const
{
	return 3;
}

template <class T>
T Vector3<T>::GetElement(int index) const
{
	if (index == 0)
	{
		return m_x;
	}
	else if (index == 1)
	{
		return m_y;
	}
	else if (index == 2)
	{
		return m_z;
	}
	else
	{
		throw std::invalid_argument("Attempt to get invalid element index.");
	}
	return 0;
}

template <class T>
void Vector3<T>::SetElement(int index, T value)
{
	if (index == 0)
	{
		m_x = value;
	}
	else if (index == 1)
	{
		m_y = value;
	}
	else if (index == 2)
	{
		m_z = value;
	}
	else
	{
		throw std::invalid_argument("Attempt to set invalid element index.");
	}
}

#endif
