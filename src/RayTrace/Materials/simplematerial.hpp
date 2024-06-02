#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "materialbase.hpp"

namespace RT
{
    class SimpleMaterial : public MaterialBase
	{
		public:
			// The default constructor and destructor
			SimpleMaterial();
			virtual ~SimpleMaterial() override;
			
			// Function to return the color
			virtual Vector<double> ComputeColor
            (
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const std::shared_ptr<RT::ObjectBase> &currentObject,
				const Vector<double> &intPoint, const Vector<double> &localNormal,
				const RT::Ray &cameraRay
            ) override;
																							
			// Function to compute specular highlights
			Vector<double> ComputeSpecular
            (
                const std::vector<std::shared_ptr<RT::ObjectBase>> &objectList,
				const std::vector<std::shared_ptr<RT::LightBase>> &lightList,
				const Vector<double> &intPoint, const Vector<double> &localNormal,
				const RT::Ray &cameraRay
            );
																				
		public:
			Vector<double> m_baseColor {std::vector<double> {1.0, 0.0, 1.0}};
			double m_reflectivity = 0.0;
			double m_shininess = 0.0;
	};
}

#endif