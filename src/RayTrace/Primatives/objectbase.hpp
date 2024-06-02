#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../../LinAlg/Vector.h"
#include "../ray.hpp"
#include "../gtfm.hpp"

namespace RT
{
    // Forward-declare the material base class. This will be overriden later
	class MaterialBase;

    class ObjectBase
    {
        public:
            // The default constructor and destructor
            ObjectBase();
            virtual ~ObjectBase();

            // Function to test for intersections
            virtual bool TestIntersection(const Ray &castRay, Vector<double> &intPoint, Vector<double> &localNormal, Vector<double> &localColor);

            // Function to transform matrix
            void SetTransformMatrix(const RT::GTform &transformMatrix);

            // Function to test whether two floating-point numbers are close to being equal
            bool CloseEnough(const double f1, const double f2);

            // Function to assign a material
            bool AssignMaterial(const std::shared_ptr<RT::MaterialBase> &objectMaterial);

        // Public member variables
        public:
            // The base colour of the object
            Vector<double> m_baseColor {3};

            // The geometric translation applied to the object
            RT::GTform m_transformMatrix;

            // A reference to the material assigned to this object
			std::shared_ptr<RT::MaterialBase> m_pMaterial;
			
			// A flag to indicate whether this object has a material or not
			bool m_hasMaterial = false;
	};
}

#endif