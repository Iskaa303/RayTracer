#include "materialbase.hpp"

// The default constructor and destructor
RT::MaterialBase::MaterialBase()
{
    m_maxReflectionRays = 3;
	m_reflectionRayCount = 0;
}

RT::MaterialBase::~MaterialBase()
{

}

// Function to return the color of the material
Vector<double> RT::MaterialBase::ComputeColor
(
    const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
	const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
	const std::shared_ptr<RT::ObjectBase> &currentObject,
	const Vector<double> &intPoint, const Vector<double> &localNormal,
	const RT::Ray &cameraRay
) {
    // Define an initial material color
    Vector<double> matColor {3};
    return matColor;
}

// Function to compute the diffuse color
Vector<double> RT::MaterialBase::ComputeDiffuseColor
(
    const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
	const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
	const std::shared_ptr<RT::ObjectBase> &currentObject,
	const Vector<double> &intPoint, const Vector<double> &localNormal,
	const Vector<double> &baseColor
) {
    // Compute the color due to diffuse illumination
	Vector<double> diffuseColor	{3};
	double intensity;
	Vector<double> color {3};
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currentLight : lightList)
	{
		validIllum = currentLight -> ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
		}
	}
	
	if (illumFound)
	{
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
	}
	
	// Return the material color
	return diffuseColor;
}

// Function to compute the color due to reflection.
Vector<double> RT::MaterialBase::ComputeReflectionColor
(
    const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
	const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
	const std::shared_ptr<RT::ObjectBase> &currentObject,
	const Vector<double> &intPoint, const Vector<double> &localNormal,
	const RT::Ray &incidentRay
) {
	Vector<double> reflectionColor {3};
	
	// Compute the reflection vector
	Vector<double> d = incidentRay.m_lab;
	Vector<double> reflectionVector = d - (2 * Vector<double>::dot(d, localNormal) * localNormal);
	
	// Construct the reflection ray.
	RT::Ray reflectionRay (intPoint, intPoint + reflectionVector);
	
	// Cast this ray into the scene and find the closest object that it intersects with
	std::shared_ptr<RT::ObjectBase> closestObject;
	Vector<double> closestIntPoint			{3};
	Vector<double> closestLocalNormal		{3};
	Vector<double> closestLocalColor		{3};
	bool intersectionFound = CastRay(reflectionRay, objectList, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
	
	// Compute illumination for closest object assuming that there was a valid intersection
	Vector<double> matColor	{3};
	if ((intersectionFound) && (m_reflectionRayCount < m_maxReflectionRays))
	{
		// Increment the reflectionRayCount
		m_reflectionRayCount++;
		
		// Check if a material has been assigned
		if (closestObject -> m_hasMaterial)
		{
			// Use the material to compute the color
			matColor = closestObject -> m_pMaterial -> ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, reflectionRay);
		}
		else
		{
			matColor = RT::MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_baseColor);
		}
	}
	else
	{
		// Leave matColor as it is
	}
	
	reflectionColor = matColor;
	return reflectionColor;
}

// Function to cast a ray into the scene.
bool RT::MaterialBase::CastRay
(
    const RT::Ray &castRay, const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
	const std::shared_ptr<RT::ObjectBase> &thisObject,
	std::shared_ptr<RT::ObjectBase> &closestObject,
	Vector<double> &closestIntPoint, Vector<double> &closestLocalNormal,
	Vector<double> &closestLocalColor
) {
	// Test for intersections with all of the objects in the scene
	Vector<double> intPoint		{3};
	Vector<double> localNormal	{3};
	Vector<double> localColor	{3};
	
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : objectList)
	{
		if (currentObject != thisObject)
		{
			bool validInt = currentObject -> TestIntersection(castRay, intPoint, localNormal, localColor);
			
			// If we have a valid intersection
			if (validInt)
			{
				// Set the flag to show that we found an intersection
				intersectionFound = true;
				
				// Compute the distance between the source and the intersection point
				double dist = (intPoint - castRay.m_point1).norm();
				
				// Store a reference to this object if it is the closest
				if (dist < minDist)
				{
					minDist = dist;
					closestObject = currentObject;
					closestIntPoint = intPoint;
					closestLocalNormal = localNormal;
					closestLocalColor = localColor;
				}
			}
		}
	}
	
	return intersectionFound;
}