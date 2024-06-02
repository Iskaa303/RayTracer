#include "pointlight.hpp"

// The default constructor
RT::PointLight::PointLight()
{
    m_color = Vector<double> {std::vector<double> {1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

// The default destructor
RT::PointLight::~PointLight()
{
    
}

// Function to compute illumination contribution
bool RT::PointLight::ComputeIllumination
(
    const Vector<double> &intPoint, const Vector<double> &localNormal,
    const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
    const std::shared_ptr<RT::ObjectBase> &currentObject,
    Vector<double> &color, double &intensity
) {
	// Construct a vector pointing from the intersection point to the light
	Vector<double> lightDir = (m_location - intPoint).Normalized();
	
	// Compute a starting point
	Vector<double> startPoint = intPoint;
	
	// Construct a ray from the point of intersection to the light.
	RT::Ray lightRay (startPoint, startPoint + lightDir);
	
	/*
        Check for intersections with all of the objects
	    in the scene, except for the current one
    */
	Vector<double> poi			{3};
	Vector<double> poiNormal	{3};
	Vector<double> poiColor		{3};
	bool validInt = false;
	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject -> TestIntersection(lightRay, poi, poiNormal, poiColor);
		}
		
		/*
            If we have an intersection, then there is no point checking further
			so we can break out of the loop. In other words, this object is
			blocking light from this light source
        */
		if (validInt)
			break;
	}

	/*
        Only continue to compute illumination if the light ray didn't
	    intersect with any objects in the scene. Ie. no objects are
		casting a shadow from this light source
    */
	if (!validInt)
	{
		// Compute the angle between the local normal and the light ray
		// Note that we assume that localNormal is a unit vector
		double angle = acos(Vector<double>::dot(localNormal, lightDir));
		
		// If the normal is pointing away from the light, then we have no illumination
		if (angle > 1.5708)
		{
			// No illumination
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else
		{
			// We do have illumination
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else
	{
		// Shadow, so no illumination
		color = m_color;
		intensity = 0.0;
		return false;
	}
}