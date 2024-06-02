#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

// Default constructor
RT::ObjectBase::ObjectBase()
{

}

// The destructor
RT::ObjectBase::~ObjectBase()
{

}

// Function to test for intersections
bool RT::ObjectBase::TestIntersection(const Ray &castRay, Vector<double> &intPoint, Vector<double> &localNormal, Vector<double> &localColor)
{
    return false;
}

// Function to transform matrix
void RT::ObjectBase::SetTransformMatrix(const RT::GTform &transformMatrix)
{
    m_transformMatrix = transformMatrix;
}

// Function to assign a material
bool RT::ObjectBase::AssignMaterial(const std::shared_ptr<RT::MaterialBase> &objectMaterial)
{
	m_pMaterial = objectMaterial;
	m_hasMaterial = true;
	return m_hasMaterial;
}

// Function to test whether two floating-point numbers are close to being equal
bool RT::ObjectBase::CloseEnough(const double f1, const double f2)
{
    return fabs(f1 - f2) < EPSILON;
}