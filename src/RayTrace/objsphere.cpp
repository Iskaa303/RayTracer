#include "objsphere.hpp"
#include <cmath>

// The default constructor
RT::ObjSphere::ObjSphere()
{

}

// The destructor
RT::ObjSphere::~ObjSphere()
{

}

// Function to test for intersections
bool RT::ObjSphere::TestIntersection
(
    const RT::Ray &castRay, Vector<double> &intPoint,
    Vector<double> &localNormal, Vector<double> &localColor
) {
    // Copy the ray and apply the backward transform
    RT::Ray bckRay = m_transformMatrix.Apply(castRay, RT::BCKTFORM);

    // Compute the values of a, b and c
    Vector<double> vhat = bckRay.m_lab;
    vhat.Normalize();

    /*
    Note that a is equal to the squared magnitude of the
    direction of the cast ray. As this will be a unit vector,
    we can conclude that the value of 'a' will always be 1
    */
    // a = 1.0;

    // Calculate b
    double b = 2.0 * Vector<double>::dot(bckRay.m_point1, vhat);

    // Calculate c
    double c = Vector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;

    // Test whether we actually have an intersection
    double intTest = (b * b) - 4.0 * c;

    Vector<double> poi;
    if (intTest > 0.0)
    {
        double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		
		/*
        If either t1 or t2 are negative, then at least part of the object is
			behind the camera and so we will ignore it
        */
		if ((t1 < 0.0) || (t2 < 0.0))
		{
			return false;
		}
		else
		{
			// Determine which point of intersection was closest to the camera
			if (t1 < t2)
			{
				poi = bckRay.m_point1 + (vhat * t1);
			}
			else
			{
				poi = bckRay.m_point1 + (vhat * t2);
			}

            // Transform the intersection point back into world coordinates
            intPoint = m_transformMatrix.Apply(poi, RT::FWDTFORM);

            // Compute the local normal (easy for a sphere at the origin)
            Vector<double> objOrigin = Vector<double>{std::vector<double>{0.0, 0.0, 0.0}};
            Vector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, RT::FWDTFORM);
            localNormal = intPoint - newObjOrigin;
            localNormal.Normalize();

            // Return the base color
            localColor = m_baseColor;
		}
		
		return true;
    }
    else
    {
        return false;
    }
}