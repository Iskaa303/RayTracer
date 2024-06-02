#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../Primatives/objectbase.hpp"
#include "../Lights/lightbase.hpp"
#include "../../LinAlg/Vector.h"
#include "../ray.hpp"

namespace RT
{
	class MaterialBase
	{
		public:
            // The default constructor and destructor
			MaterialBase();
			virtual ~MaterialBase();
			
			// Function to return the color of the material
			virtual Vector<double> ComputeColor
            (
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const Vector<double> &intPoint, const Vector<double> &localNormal,
				const RT::Ray &cameraRay
            );
																							
			// Function to compute the diffuse color
			static Vector<double> ComputeDiffuseColor
            (
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const Vector<double> &intPoint, const Vector<double> &localNormal,
				const Vector<double> &baseColor
            );
																										
			// Function to compute the reflection color
			Vector<double> ComputeReflectionColor
            (
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const Vector<double> &intPoint, const Vector<double> &localNormal,
				const RT::Ray &incidentRay
            );
																										
			// Function to cast a ray into the scene
			bool CastRay
            (
                const RT::Ray &castRay, const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::shared_ptr<RT::ObjectBase> &thisObject,
				std::shared_ptr<RT::ObjectBase> &closestObject,
				Vector<double> &closestIntPoint, Vector<double> &closestLocalNormal,
				Vector<double> &closestLocalColor
            );
										
		public:
			// Counter for the number of relection rays
			inline static int m_maxReflectionRays;
			inline static int m_reflectionRayCount;
		
		private:
		
	};
}

#endif